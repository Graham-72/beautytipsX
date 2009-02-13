if (Drupal.jsEnabled) {
  $(document).ready(function() {
  	$('form .form-item input.form-text + .description').hide().prev('input').bt({
	    trigger: ['focus', 'blur'],
	    positions: [bt_direction]
	  });
  });
}