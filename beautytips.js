Drupal.behaviors.beautytips = function() {
    for( key in Drupal.settings.beautytips) {
      $(Drupal.settings.beautytips[key]['area'][0]).each(function() {
        var description = $(this).parents('.form-item').find('.description').hide().html();
        if (description && Drupal.settings.beautytips[key]['description'][0]) {
          $(this).bt(description, {
            trigger: [Drupal.settings.beautytips[key]['trigger'][0], Drupal.settings.beautytips[key]['trigger'][1]],
  	        positions: [bt_direction],
            ajaxPath: Drupal.settings.beautytips[key]['ajaxPath'][0] + Drupal.settings.beautytips[key]['ajaxDiv'][0]
          });
        }
        else if (!Drupal.settings.beautytips[key]['description'][0]) {
          $(this).bt({
            trigger:  Drupal.settings.beautytips[key]['trigger'][0],
            ajaxPath:  Drupal.settings.beautytips[key]['ajaxPath'][0] + Drupal.settings.beautytips[key]['ajaxDiv'][0],
            width: 300,
            cssStyles: {width: 'auto', paddingTop: 0, paddingBottom: 0},
          });
        }
      });
    }
}