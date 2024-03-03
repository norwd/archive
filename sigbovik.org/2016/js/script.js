$(document).ready(function(){
  /* fix navbar-toggle colors */
  $('#navbar-sigboviks-years').on('hidden.bs.collapse', function () {
    $('#navbar-sigboviks .navbar-toggle').css('background-color','transparent')});
  $('#navbar-sigboviks-years').on('show.bs.collapse', function () {
    $('#navbar-sigboviks .navbar-toggle').css('background-color','#ddd')});

  /* replace Q's with middle names */
  $('.q').replaceWith(function () { return randOf(middleNames); });

  /* replace subjects with random ones */
  $('.subject').replaceWith(function () { return randOf(subjects); });
});

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

