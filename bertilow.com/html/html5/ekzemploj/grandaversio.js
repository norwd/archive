$( function() {
	$('#katoj a').each( function() {
		var a = this;
		var img = $(a).find('img')[0];
		if (a && img) {
			var malgrandaversio = img.getAttribute('src');
			var grandaversio = img.getAttribute('data-grandaversio');
			var originatitle = img.getAttribute('title');
			var title = img.getAttribute('data-title');
			if (malgrandaversio && grandaversio && originatitle && title) {
				img.setAttribute('title', title);
				$(img).click( function() {
					if (!$(img).hasClass('granda')) {
						$(img).addClass('granda');
						img.setAttribute('src', grandaversio);
						img.setAttribute('title', originatitle);
						return false;
					}
				});
				$(img).mouseout( function() {
					if ($(img).hasClass('granda')) {
						$(img).removeClass('granda');
						img.setAttribute('src', malgrandaversio);
						img.setAttribute('title', title);
						return false;
					}
				});
			}
		}
	});
});
