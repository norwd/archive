$(document).ready(function(){
  /* fix navbar-toggle colors */
  $('#navbar-sigboviks-years').on('hidden.bs.collapse', function () {
    $('#navbar-sigboviks .navbar-toggle').css('background-color','transparent')});
  $('#navbar-sigboviks-years').on('show.bs.collapse', function () {
    $('#navbar-sigboviks .navbar-toggle').css('background-color','#ddd')});

  /* set up navbar-2015 anchor handlers */
  $('#navbar-2015-venue').click(function () {return jumpTo('#venue')});
  $('#navbar-2015-scope').click(function () {return jumpTo('#scope')});
  $('#navbar-2015-proceedings').click(function () {return jumpTo('#proceedings')});
  $('#navbar-2015-submission').click(function () {return jumpTo('#submission')});
  $('#navbar-2015-listserv').click(function () {return jumpTo('#listserv')});

  /* replace Q's with middle names */
  $('.q').replaceWith(function () { return randOf(middleNames); });

  /* replace subjects with random ones */
  $('.subject').replaceWith(function () { return randOf(subjects); });

  positionElements();
  window.setTimeout(function() { centerText('#scope'); }, 100);

  prepAnimations();
  checkAnimations();
});

/* position various elements */
function positionElements() {
  $('.section').height(Math.min(Math.max($(window).height() * .9,500),800));

  centerText('#title');
  centerText('#submission');
  centerText('#proceedings');
  centerText('#listserv');
  centerText('#venue');
  $('#scope > video').css({
    'margin-left': ($(window).width() - 1920)/2
  });
}
$(window).resize(positionElements);
// webkit is terrible at onresize; horrible workaround follows
$(window).resize(function() {
  window.setTimeout(function() { centerText('#scope'); }, 100);
});

/* lock the bottom navbar */
function lockNavbar() {
  if ($(this).scrollTop() > 50) {
    $('#navbar-2015').addClass('navbar-fixed-top');
    $('#header').addClass('navbar-is-locked');
  } else {
    $('#navbar-2015').removeClass('navbar-fixed-top');
    $('#header').removeClass('navbar-is-locked');
  }
}
$(window).on('scroll', lockNavbar);
$(window).on('touchmove', lockNavbar);

var unseen = ['#title','#venue','#scope','#proceedings','#submission','#listserv'];
function checkAnimations() {
  $.each(unseen, function(i,id) {
    if (isVisible($(id + ' .text'))) {
      doAnimation(id);
      unseen.splice(i,1);
      return false;
    } else {
      return true;
    }
  });
}
$(window).on('scroll', checkAnimations);
$(window).on('touchmove', checkAnimations);

function prepAnimations() {
  $.each(['#title','#venue','#scope','#proceedings','#submission','#listserv'], function(i,id) {
    $(id + ' .text').css({opacity: 0, 'margin-top': '-=20'});
  });
}

function doAnimation(id) {
  switch(id) {
    case '#title':
    case '#venue':
    case '#scope':
    case '#proceedings':
    case '#submission':
    case '#listserv':
      $(id + ' .text').animate({
        opacity: 1, 'margin-top': '+=20'
      },600);
      break;
  }
}

/* account for navbar's height when jumping to sections */
function jumpTo(id) {
  $('html,body').scrollTop($(id).offset().top - $('#navbar-2015').height() - 1);
  return false;
}

function centerText(id) {
  $(id + '> .text').css({
    'position': 'absolute',
    'margin-left': ($(id).width() - $(id + '> .text').outerWidth())/2,
    'margin-top': ($(id).height() - $(id + '> .text').outerHeight())/2
  });
}

function isVisible(o) {
  var wt = $(window).scrollTop();
  var wb = wt + $(window).height();
  var ot = o.offset().top;
  var ob = ot + o.height();
  return ((ob < wb) && (ot > wt));
}

function randOf(arr) {
  return arr[Math.floor(Math.random() * arr.length)];
}

var middleNames = [ 'Quine', 'Quandle', 'Quark', 'Querulous', 'Qatar', 'Qed',
'Qoph', 'Quacksalver', 'Quadragesimal', 'Quadratosquamosal', 'Quadrophonic',
'Quadriplegic', 'Quaequae', 'Quaestio', 'Quaffingly', 'Quag', 'Quagga',
'Quagmiry', 'Quaint-costumed', 'Quailberry', 'Quakeproof', 'Quakerproof',
'Qualia', 'Quale', 'Qualmish', 'Quamasia', 'Quango', 'Quantization',
'Quantifiability', 'Quantile', 'Quantong', 'Quantz', 'Quarterback',
'Quarter-dollar', 'Quartet', 'Quartz-crystal', 'Quasi-bovik', 'Quechua',
"Queen-o'-the-prairie", 'Queensland', 'Quelquechose', 'Queneau', 'Query',
'Quernstone', 'Questionable', 'Quetzcoatl', 'Queue', 'Quibble', 'Quickbeam',
'Quick-freeze', 'Quicksand', 'Quicksilver', 'Quidditch', 'Quiescent', 'Quimby',
'Quince', 'Quincunx', 'Quinine', 'Quintessentially', 'Quip', 'Quirk',
'Quixotic', 'Quiver', 'Quizmaster', 'Quo', 'Quokka', 'Qouit', 'Quondam',
'Quorum', 'Quota', 'Qwerty' ];

var subjects = [ 'Adaptive Cruise Control', 'Mean Sojourn Time',
'Fitness Landscapes', 'Cloud Rendering', 'Sticky-Finger Manipulation', 
'Ancestral Genetic Processes', 'Computational Archaeolinguistics',
'Cloud Offload in Hostile Environments', 'Diversity at the Edge',
'Neuronal Networks', 'Robot Policy Learning', 'Selfish Behavior in Games',
'Generalized Evidence', 'Worm Causality', 'Discard-based Search',
'Retroactive Data', 'Mixed Procurement', 'State Dominance', 'Blog Shapes',
'Agnostic Active Learning', 'Private Stream Searching',
'Regret-Minimizing Algorithms', 'k-Armed Bandits', 'Self-Adjusting Computation',
'Integer-Based Vulnerabilities', 'Generalized Belief', 'Inept Expert Systems',
'Deep Space Navigation', 'Science', 'Perplexity Theory',
'Thaughmaturgic Circle', 'Denotational Semantics of Pidgin and Creole', 
'Anomaly Detection', 'Hashing with Deletion', 'Dynamic Mesh Refinement',
'Phylogenetics', 'Natural Intelligence', 'Artificial Stupidity', 
'Rasterized Love Triangles', 'Synergistic Hyperparadigmatism' ];

