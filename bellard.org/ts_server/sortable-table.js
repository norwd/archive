"use strict";

/* dir: -1 = descending, 1 = ascending */
function sortColumn(tableNode, columnIndex, isNumber, dir)
{
    function compare(a1, a2) {
        var v1 = a1.value;
        var v2 = a2.value;
        if (v1 == v2)
            return 0;
        else if (v1 < v2)
            return -dir;
        else
            return dir;
    }

    var tbodyNode = tableNode.querySelector('tbody');
    var rowNodes = [];
    var dataCells = [];

    var rowNode = tbodyNode.firstElementChild;

    var index = 0;

    while (rowNode) {
      rowNodes.push(rowNode);
      var rowCells = rowNode.querySelectorAll('th, td');
      var dataCell = rowCells[columnIndex];

      var data = {};
      data.index = index;
      data.value = dataCell.textContent.toLowerCase().trim();
      if (isNumber) {
          data.value = parseFloat(data.value);
      }
      dataCells.push(data);
      rowNode = rowNode.nextElementSibling;
      index += 1;
    }

    dataCells.sort(compare);

    // remove rows
    while (tbodyNode.firstChild) {
      tbodyNode.removeChild(tbodyNode.lastChild);
    }

    // add sorted rows
    for (var i = 0; i < dataCells.length; i++) {
      tbodyNode.appendChild(rowNodes[dataCells[i].index]);
    }
}

function handleButtonClick(columnIndex, ev)
{
    var columnHeaders = this.querySelectorAll('thead th');
    var isNumber, dir;
    
    
    /* informative only: set aria-sort */
    for(var i = 0; i < columnHeaders.length; i++) {
        var ch = columnHeaders[i];
        if (i == columnIndex) {
            var buttonNode = ch.querySelector('button');
            isNumber = ch.classList.contains('num');
            var str = ch.getAttribute('aria-sort');
            if (str == "descending")
                dir = 1;
            else
                dir = -1;
            ch.setAttribute('aria-sort', dir < 0 ? 'descending' : 'ascending');
        } else {
            ch.removeAttribute('aria-sort');
        }
    }
//    console.log("col=", columnIndex, "isnum=", isNumber, "dir=", dir)
    sortColumn(this, columnIndex, isNumber, dir)
}

window.addEventListener("load", function() {
    var tab = document.querySelectorAll('table.sortable');
    for(var i = 0; i < tab.length; i++) {
        var tableNode = tab[i];
        var columnHeaders = tableNode.querySelectorAll('thead th');
        for(var j = 0; j < columnHeaders.length; j++) {
            var ch = columnHeaders[j];
            var buttonNode = ch.querySelector('button');
            if (buttonNode) {
                buttonNode.addEventListener('click', handleButtonClick.bind(tableNode, j));
            }
        }
    }
});
