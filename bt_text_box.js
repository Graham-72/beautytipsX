Drupal.behaviors.bt_text_box = function() {
  var selector = ['bt_text_field', 'bt_text_area'];
  for (var i = 0; i < selector.length; i++) {
    $(Drupal.settings.beautytips[selector[i]]['area']).each(function() {
      var description = $(this).parents('.form-item').find('.description').hide().html();
      if (description) {
        $(this).bt(description, {
          trigger: Drupal.settings.beautytips[selector[i]]['trigger'],
          positions: Drupal.settings.beautytips[selector[i]]['position'],
        });
      }
    });
  }  
}