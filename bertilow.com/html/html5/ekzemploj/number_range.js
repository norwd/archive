$( function() {
	var formularo = $('form')[0];
	if (formularo) {
		$(formularo).find('input[type=range]').each( function() {
			var range = this;
			var min, max, valoro;
			min = range.getAttribute('min') || 0;
			max = range.getAttribute('max') || 100;
			if (!min) {
				min = 0;
			}
			if (!max) {
				max = 100;
			}
			valoro = range.getAttribute('value') || (min + (max-min)/2);
			$(range).val(valoro);
			var valorospan = $('<span>= ' + valoro.replace(/\./, ',') + '</span>');
			$(range).after(valorospan);
			$(range).change( function() {
				valoro = $(this).val();
				valoro = Math.round(valoro*100)/100 + '';
				$(valorospan).html('= ' + valoro.replace(/\./, ','));
			});
		});
	}
	var mesagho = $('#mesagho')[0];
	if (mesagho) {
		$(mesagho).html('(La posta montrado de la valoro de la <code>range</code>-kampo estas kreita per Javaskripta kodo. Sen tio, en TTT-legiloj, kiuj montras ŝovregilon por <code>range</code>-kampoj, la efektiva valoro tute ne montriĝas, almenaŭ ne en tiuj TTT-legiloj, kiujn mi testis. Por tia montrado mi kredeble devus uzi <code>output</code>-elementon, sed ĉi tie mi ne volis testi samtempe tro multajn novajn elementojn.)');
	}
});
