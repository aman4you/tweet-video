<div class="campaign-quiz-bank quiz-questions col-sm-8">
  <?php if ($quiz): ?>
    <div class="hide campaign-quiz"><?php print $quiz ?></div>
  <?php endif; ?>
  <?php if ($quiz_question): ?>
    <div class="quiz-header">
      <div class="question-bank"><span class="question-text">Question Bank</span></div>
      <div class="link all-quiz-question">Click Here To View The Entire List Of Questions</div>
    </div>
    <div class="quiz-content">
      <span class="previous"></span>
      <div class="campaign-quiz-question">
        <?php print $quiz_question; ?>
      </div>
      <span class="next"></span>
    </div>
  <?php endif; ?>
</div>

<?php if (!empty($twitter_widget_id) && !empty($hashtag)): ?>
  <div class="hcl-campaign-twitter-widget col-sm-4">
  <div class="hcl-campaign-twitter-widget-header">Twitter Live Feed</div>
    <a class="twitter-timeline" href="https://twitter.com/hashtag/"<?php print $hashtag ?> data-widget-id=<?php print $twitter_widget_id ?> data-chrome="noheader"><?php print '#' . $hashtag ?> Tweets</a>
    <script>!function(d,s,id){var js,fjs=d.getElementsByTagName(s)[0],p=/^http:/.test(d.location)?'http':'https';if(!d.getElementById(id)){js=d.createElement(s);js.id=id;js.src=p+"://platform.twitter.com/widgets.js";fjs.parentNode.insertBefore(js,fjs);}}(document,"script","twitter-wjs");</script>
  </div>
<?php endif; ?>
