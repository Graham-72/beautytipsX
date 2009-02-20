if (Drupal.jsEnabled) {
  $(document).ready(function() {
    var text = ['textarea.form-textarea', '.form-text'];
    for (var i = 0; i < text.length; i++) {
      $(text[i]).each(function() {
        var description = $(this).parents('.form-item').find('.description').hide().html();
        if (description) {
          $(this).bt(description, {
            trigger: ['focus', 'blur'],
  	        positions: [bt_direction]
          });
        }
      });
    }
    if (bt_drupal_help) {
	  $('.more-help-link a').each(function() {
	    $(this).bt({
		  width: 300,
		  ajaxPath: $(this).attr('href') + '#squeeze.clear-block p',
		  cssStyles: {width: 'auto', paddingTop: 0, paddingBottom: 0},
		  cornerRadius: 15,
		  strokeStyle: 'rgb(45, 72, 103)',
		  ajaxLoading: '<p><blink>Loading...</blink></p>'
	    });
	  });
    }
  });
}