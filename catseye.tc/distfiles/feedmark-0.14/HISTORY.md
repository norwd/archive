History of Feedmark
===================

0.14
----

*   Generated anchors are now compatible with those on GitHub
    (multiple spaces are not coalesced into a single hyphen.)
*   Fixed bug with schema checking where, if multiple documents
    were given on command line, not all documents were checked.

0.13
----

*   The default interpreter for the `feedmark` script is now
    `python3`.
*   The test harness runs tests under Python 2, or Python 3,
    or both, depending on what's available.

0.12
----

*   Added support for hyperlinks on images on entries.
*   Added test cases for correct handling of images on entries.
*   Format of entry images in output JSON has changed: each image
    is now represented as a dictionary with two or three keys
    rather than as a list with two elements.

0.11
----

*   Fixed a bug with `--rewrite-markdown` under Python 3.x.

0.10
----

*   Format of refdex files has changed: an entry can now have a
    key `filenames`, which is like `filename`, but can be a list.
    This is backwards-compatible on input, and you can pass the
    flag `--output-refdex-single-filename` to cause the output
    from `--output-refdex` to strip all but the last filename
    and produce only `filename` entries on output.
*   Parser now allows trailing `###` on h3-level section headers.

0.9-2019.1015
-------------

*   Minor release to work out issues with `setup.py`.

0.9
---

*   Added conventional `--version` option to `feedmark`.
*   Added `setup.py` so that Feedmark can be treated as a Python
    package.

0.8
---

*   Added `--htmlized-json` option which, when using `--output-json`,
    converts Markdown to HTML5 every place it is present in the JSON.
*   Added `--ordered-json` option which, when using `--output-json`,
    serializes the properties (of the document and of each section)
    as an array of two-element arrays, instead of a JSON object.

0.7
---

*   Renamed `link-to-anchors-on` property to `link-target-url`.
*   Improved unit tests.

0.6
---

*   Uses the `toc` extension that ships with `markdown` to generate
    heading-anchors (instead of a home-rolled function for that.)
*   Heading anchors are generated on all header levels, not just `h3`.
*   Format in which links extracted from documents are output in JSON
    has changed.  Each link is a dictionary, includes more info.
*   Able to output links that don't appear in any Feedmark section.
*   Ability to archive targets of links has been split off into a
    separate utility (called `yastasoti` and hosted in its own repo)
    which consumes the new link JSON format.
*   Tests are an actual Python unittest suite, which passes when run
    under Python 3.

0.5
---

*   Format of JSON written by `--output-json` cleaned up; documents
    are given in a list, sections in a document are also in lists.
*   Functionality for generating a table of contents has been removed.
    Example script that generates a ToC from `feedmark --output-json`
    is provided in the `eg` directory instead.

0.4
---

*   Checking links now works for local files; it checks they are in
    the directory specified as `--article-root`.
*   Archiving targets of links is "more idempotent":
    *   if the file has not changed, it is not changed on disk
    *   if it has changed, the old file is renamed to a datestamped name
    *   `--archive-missing-only` only downloads if not already have it
*   Writing the anchor `id` of `h3` elements is now much faster, as it
    is now done with a Markdown extension instead of BeautifulSoup.
*   `preamble` of a document is now formatted the same way as the `body`
    of each section in the document.
*   HISTORY document.
*   Other small fixes.

0.3
---

*   Output JSON with `--output-json`.  Also `--by-publication-date`.
*   Output links with `--output-links`.
*   Multiple input refdexes can be read with `--input-refdexes`.
*   A prefix can be virtually appended to every filename in the
    input refdexes using `--input-refdex-filename-prefix`.
*   Output a table of contents.
*   Some internal refactoring.
*   Rudimentary test suite.
*   Other small fixes.

0.2
---

*   Check documents against schema.
*   Check, and archive the targets of, links in documents.
*   Output Markdown and HTML from input Feedmark documents.
*   Rewrite Feedmark documents in-place.
*   Create and use a refdex file (reference-style links.)
*   Other small fixes.

0.1
---

*   Initial release.
*   Ability to create an Atom feed from a Markdown document.
