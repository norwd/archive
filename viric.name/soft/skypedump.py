#!/usr/bin/env python

import Skype4Py
import logging
import datetime
import codecs
import os

logging.getLogger('Skype4Py').setLevel(logging.DEBUG)

# Instatinate Skype object, all further actions are done
# using this object.
skype = Skype4Py.Skype(None, Transport='x11')

# Start Skype if it's not already running.
if not skype.Client.IsRunning:
    skype.Client.Start()

# Set our application name.
skype.FriendlyName = 'ChatDump'

# Attach to Skype. This may cause Skype to open a confirmation
# dialog.
skype.Attach()

# Set up an event handler.
def new_skype_status(status):
    # If Skype is closed and reopened, it informs us about it
    # so we can reattach.
    if status == Skype4Py.apiAttachAvailable:
        skype.Attach()
skype.OnAttachmentStatus = new_skype_status

def timestamp2txt(timestamp):
    return datetime.fromtimestamp(int(timestamp))

try:
    os.mkdir("per-user")
except os.error:
    None

def findtxtname(base):
    if not os.path.exists(base + '.txt'):
        return base;
    count = 1;
    while os.path.exists(base + '-' + str(count) + '.txt'):
        count += 1
    return base + '-' + str(count)

for i in skype.Chats:
    isodate = i.Datetime.isoformat()
    basename = findtxtname(isodate)
    f = codecs.open(basename + '.txt', 'w', 'utf8')
    f.write('TIMESTAMP: ' + isodate + '\n')
    print basename + '; ' + i.Topic
    f.write(u'TOPIC: ' + i.Topic + u'\n')
    f.write(u'FRIENDLYNAME: ' + i.FriendlyName + u'\n')
    f.write(u'MEMBERS: ')

    first = True
    ulist = []
    for u in i.Members:
        if not first:
            f.write(u', ')
        f.write(u.Handle)
        dirname = 'per-user/' + u.Handle
        try:
            os.mkdir(dirname)
        except os.error:
            None
        os.symlink('../../' + basename+'.txt', dirname + '/' + basename + '.txt')
        ulist += [ u.Handle ]
        first = False
    f.write(u'\n')

    if len(ulist) > 1:
        dirname = 'per-user/' + ",".join(sorted(ulist))
        try:
            os.mkdir(dirname)
        except os.error:
            None
        os.symlink('../../' + basename +'.txt', dirname + '/' + basename + '.txt')

    for m in reversed(i.Messages):
        middle = ':'
        if m.Type != 'SAID':
            middle = u' ' + m.Type
        f.write(m.Datetime.isoformat() + u' ' + m.FromHandle + middle + u' ' + m.Body + '\n')

    f.close()

