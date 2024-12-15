window.onload = function() {
  var desegnoTolajho = document.getElementById('desegnejo');
  if (desegnoTolajho && desegnoTolajho.getContext) {
    var kunteksto = desegnoTolajho.getContext('2d');

    kunteksto.strokeStyle = "#000000";
    kunteksto.fillStyle = "#FFFF00";
    kunteksto.beginPath();
    kunteksto.arc(100,100,50,0,Math.PI*2,true);
    kunteksto.closePath();
    kunteksto.stroke();
    kunteksto.fill();

    kunteksto.strokeStyle = "#000000";
    kunteksto.fillStyle = "#FFFFFF";
    kunteksto.beginPath();
    kunteksto.arc(80,80,8,0,Math.PI*2,true);
    kunteksto.closePath();
    kunteksto.stroke();
    kunteksto.fill();

    kunteksto.fillStyle = "#009966";
    kunteksto.beginPath();
    kunteksto.arc(80,80,5,0,Math.PI*2,true);
    kunteksto.closePath();
    kunteksto.fill();

    kunteksto.strokeStyle = "#000000";
    kunteksto.fillStyle = "#FFFFFF";
    kunteksto.beginPath();
    kunteksto.arc(120,80,8,0,Math.PI*2,true);
    kunteksto.closePath();
    kunteksto.stroke();
    kunteksto.fill();

    kunteksto.fillStyle = "#009966";
    kunteksto.beginPath();
    kunteksto.arc(120,80,5,0,Math.PI*2,true);
    kunteksto.closePath();
    kunteksto.fill();

    kunteksto.fillStyle = "#000000";
    kunteksto.beginPath();
    kunteksto.moveTo(93,100);
    kunteksto.lineTo(100,93);
    kunteksto.lineTo(107,100);
    kunteksto.lineTo(100,107);
    kunteksto.closePath();
    kunteksto.fill();

    kunteksto.strokeStyle = "#000000";
    kunteksto.beginPath();
    kunteksto.moveTo(70,110);
    kunteksto.quadraticCurveTo(100,150,130,110);
    kunteksto.quadraticCurveTo(100,150,70,110);
    kunteksto.closePath();
    kunteksto.stroke();
  }
}
