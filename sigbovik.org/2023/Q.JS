function randOf(arr) {
  return arr[Math.floor(Math.random() * arr.length)];
}

const middleNames = [ 'Quine', 'Quandle', 'Quark', 'Querulous', 'Qatar', 'Qed',
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

document.getElementById('Q').innerHTML = randOf(middleNames);
