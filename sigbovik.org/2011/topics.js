var TOPICS = [
/* Gleaned from the 2010 CMU CS Tech Reports */
"Diversity at the Edge",
"Neuronal Networks",
/* Gleaned from the 2009 CMU CS Tech Reports */
"Robot Policy Learning",
"Selfish Behavior in Games",
/* Gleaned from the 2008 CMU CS Tech Reports */
"Generalized Evidence",
"Expandable Grids",
"Evolution Styles",
/* Gleaned from the 2007 CMU CS Tech Reports */
"Worm Causality",
"Discard-based Search",
"Opaque Quorum Systems",
"Dynamic Mesh Refinement",
"Retroactive Data",
"Mixed Procurement",
"State Dominance",
"Haptic Rendering",
"Blog Shapes",
"Agnostic Active Learning",
/* 2006 Tech Reports */
"Private Stream Searching",
"Regret-Minimizing Algorithms",
"k-Armed Bandits",
"Self-Adjusting Computation",
"Integer-Based Vulnerabilities",
"Spatio-Temporal Clusters",
"Hashing with Deletion",
"Generalized Belief"
];

var NUM_TOPICS = 4;

function arrayContains(arr, len, el) {
    var i;

    for (i = 0; i < len; i++) {
        if (arr[i] == el)
            return true;
    }

    return false;
}

var topics = new Array();
for (i = 0; i < NUM_TOPICS; i++) {
    do {
        topics[i] = TOPICS[Math.floor(Math.random() * TOPICS.length)];
    } while (arrayContains(topics, i, topics[i]));
}

var element = document.getElementById("topics");
element.innerHTML = topics.join(", ");
