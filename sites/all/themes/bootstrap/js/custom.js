(function ($, Drupal, window, document, undefined) {
  $(document).ready(function() {

    // If question not exist, hide question block.
    TotalQuestion = $(".quiz-question").length;
    if (TotalQuestion == 0) {
      $(".quiz-content").hide();
    }

    // If only one question exist, hide previous and next image.
    TotalQuestion = $(".quiz-question").length;
    if (TotalQuestion == 1) {
      $(".next").hide();
      $(".previous").hide();
    }

    /*
    If two or more question exist.
    To perform action on next image.
    */
    $(".next").click(function() {
      // Fade in image previous
      $(".previous").fadeTo("fast", 1);
      // Iterate all quiz questions.
      $(".quiz-question").each(function(index, value) {
        // Get current element.
        if ($(this).hasClass('show') == true) {
          // If element a top element.
            if (index + 1 == 1) {
              $(this).attr("class", "quiz-question top");
              // If next element a last element.
              if (index + 2 == TotalQuestion) {
                $(this).next().attr("class", "quiz-question last show");
              }
              else {
                $(this).next().attr("class", "quiz-question show");
              }
              return false;
            }
            // If element a last element.
            else if (index + 1 == TotalQuestion) {
              $(".next").fadeTo("fast", 0.5);
              return false;
            }
            // if element a middle element.
            else {
              $(this).attr("class", "quiz-question");
              // if next element a last element.
              if (index + 2 == TotalQuestion) {
                $(this).next().attr("class", "quiz-question last show");
              }
              else {
                $(this).next().attr("class", "quiz-question show");
              }
              return false;
            }
        }
      });
    });

    // To perform action on previous image.
    $(".previous").click(function() {
      // Fade in image next
      $(".next").fadeTo("fast", 1);
      // Iterate all quiz questions.
      $(".quiz-question").each(function(index, value) {
        // Get current element.
        if ($(this).hasClass('show') == true) {
          // If element a last element.
            if (index + 1 == TotalQuestion) {
              $(this).attr("class", "quiz-question last");
              // If previous element a first element.
              if (index == 1) {
                $(this).prev().attr("class", "quiz-question first show");
              }
              else {
                $(this).prev().attr("class", "quiz-question show");
              }
              return false;
            }
            // If element a first element.
            else if (index == 0) {
              $(".previous").fadeTo("fast", 0.5);
              return false;
            }
            // If element a middle element.
            else {
              $(this).attr("class", "quiz-question");
              // If previous element a first element.
              if (index == 1) {
                $(this).prev().attr("class", "quiz-question first show");
              }
              else {
                $(this).prev().attr("class", "quiz-question show");
              }
              return false;
            }
        }
      });
    });

    // On hover change mouse cursor
    $(".next, .previous").hover(function() {
      $(this).css("cursor", "pointer");
    });
  });
})(jQuery, Drupal, this, this.document);
