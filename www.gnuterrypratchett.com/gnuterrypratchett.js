function toggle(x) {
	
	var container = document.getElementById(x);
	var clickthisthing = container.getElementsByTagName("div")[0];
	
	if (container.className == 'show') {
		
		container.className = 'hide';
		clickthisthing.textContent = "+";
		
	} else {
		
		container.className = 'show';
		clickthisthing.textContent = "-";
		
	}
	
}