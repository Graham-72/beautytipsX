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
  });
}