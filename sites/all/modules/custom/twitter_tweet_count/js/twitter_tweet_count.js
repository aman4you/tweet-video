(function ($, Drupal, window, document, undefined) {
  $(document).ready(function() {

    var hcl_tweets_count = Drupal.settings.total_tweets_count.hcl_tweets_count;
    var default_video = Drupal.settings.total_tweets_count.default_video;
    var default_image = Drupal.settings.total_tweets_count.default_image;

    change_video_link(default_video, default_image);
    change_twitter_count_meter(hcl_tweets_count);
    setTimeout(get_tweet_count, 5000);

    function get_tweet_count() {
      var current = jwplayer("hcl-campaign-video-player").getPlaylistItem();
      video_name = current.file;
      var total_tweets_count = $('.total_tweets_count').html();
      quiz = $('.campaign-quiz').html();
      $.post("sites/all/modules/custom/twitter_tweet_count/twitter_count.php", {video_name: video_name, total_tweets_count: total_tweets_count, quiz: quiz}, function(data) {
        data = $.parseJSON(data);

        $('.total_tweets_count').html(data.total_tweets_count);
        var hcl_tweet_counts = data.hcl_tweets_count;
        var image_preview = data.image_name;
        var video_name = data.video_name;
        var video_name_change = data.video_name_change;
        var is_quiz_question_update = data.is_quiz_question_update;
        var update_quiz_question = data.update_quiz_question;
        if (video_name_change) {
          change_video_link(video_name, image_preview);
        }
        change_twitter_count_meter(hcl_tweet_counts);
        setTimeout(get_tweet_count, 5000);
        if (is_quiz_question_update) {
          get_new_quiz_question();
          $('.campaign-quiz').html(update_quiz_question);
        }
      });
    }

    function change_twitter_count_meter(hcl_tweets_count) {
      var total_tweets_count = $('.total_tweets_count').text();
      count = 0;
      var number_of_filled_cell = 0;
      var tweets_count_counter = 0;

      for (var i = 0; i < hcl_tweets_count.length; i++) {

        tweets_count_counter = parseInt(tweets_count_counter) + parseInt(hcl_tweets_count[i]);
        if (total_tweets_count >= tweets_count_counter) {
          number_of_filled_cell++;
          continue;
        }
        break;
      }

      remaining_incomplete_cell = (tweets_count_counter - total_tweets_count) / hcl_tweets_count[number_of_filled_cell] * 100;
      remaining_complete_cell = 100 - remaining_incomplete_cell;

      $('.cell').each(function() {
        $(this).find('.cell-box').removeClass('remaining-cell');
        $(this).find('.cell-box').removeClass('complete-cell');
        if (count < number_of_filled_cell) {
          $(this).find('.cell-box').removeClass('remaining-cell');
          $(this).find('.cell-box').addClass('complete-cell');
        }
        if (count == number_of_filled_cell) {
          $(this).find('.cell-box').removeClass('complete-cell');
          $(this).find('.cell-box').addClass('remaining-cell');
        }
        $(this).find('.cell-box').html('');
        count++;
      });

      $('.remaining-cell').html('');
      $('.remaining-cell').append('<span class="remaining-complete-cell"></span><span class="remaining--cell"></span>');
      $('.remaining-complete-cell').css('width', remaining_complete_cell + '%');
    }

    function change_video_link(video_name, image_preview) {
      jwplayer("hcl-campaign-video-player").setup({
          file: video_name,
          image: image_preview,
          height: 350,
      });
    }


    //** Quiz Javascript **//

    quiz_arrow();

    // On previous button click of quiz question.
    $('.campaign-quiz-bank .previous').click(function() {
      var current_question = $('.campaign-quiz-bank .quiz-question.show');
      if (!current_question.hasClass('top')) {
        var prev = current_question.prev();
        current_question.removeClass('show');
        prev.addClass('show');
      }
      quiz_arrow();
    });

    // On next button click of quiz question.
    $('.campaign-quiz-bank .next').click(function() {
      var current_question = $('.campaign-quiz-bank .quiz-question.show');
      if (!current_question.hasClass('last')) {
        var next = current_question.next();
        current_question.removeClass('show');
        next.addClass('show');
      }
      quiz_arrow();
    });

    function quiz_arrow() {
      $('.campaign-quiz-bank .previous, .campaign-quiz-bank .next').removeClass('high-brightness');
      $('.campaign-quiz-bank .previous, .campaign-quiz-bank .next').removeClass('low-brightness');
      if ($('.campaign-quiz-bank .quiz-question.top.show').length > 0) {
        $('.campaign-quiz-bank .previous').removeClass('high-brightness');
        $('.campaign-quiz-bank .previous').addClass('low-brightness');
        $('.campaign-quiz-bank .next').removeClass('low-brightness');
        $('.campaign-quiz-bank .next').addClass('high-brightness');
      }
      if ($('.campaign-quiz-bank .quiz-question.last.show').length > 0) {
        $('.campaign-quiz-bank .previous').addClass('high-brightness');
        $('.campaign-quiz-bank .previous').removeClass('low-brightness');
        $('.campaign-quiz-bank .next').addClass('low-brightness');
        $('.campaign-quiz-bank .next').removeClass('high-brightness');
      }
    }

    function get_new_quiz_question() {
      $.post("ajax/get-campaign-quiz", {}, function(data) {
        $('.quiz-question').removeClass('top');
        $('.quiz-question').removeClass('show');
        var quiz = $('.campaign-quiz-question').html();
        data = '<div class="quiz-question top show">' + data + '</div>';
        $('.previous').removeClass('high-brightness');
        $('.previous').addClass('low-brightness');
        quiz = data + quiz;
        $('.campaign-quiz-question').html(quiz);
        quiz_arrow();
      });
    }

  });
})(jQuery, Drupal, this, this.document);
