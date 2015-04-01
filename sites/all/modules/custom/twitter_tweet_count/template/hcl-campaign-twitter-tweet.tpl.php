<div class="campaign-video col-lg-offset-2 col-lg-5">
  <div id="hcl-campaign-video-player">Loading the player...</div>
</div>

<div class="hcl-campaign-tweet-meter-wrapper col-xs-offset-2 col-xs-8 col-sm-offset-2 col-lg-offset-0 col-sm-8 col-lg-3">
  <div class="hcl-campaign-tweet-meter-outer">
    <div class="hcl-campaign-tweet-meter-inner">
      <div class="hcl-campaign-tweet-meter-icon"></div>
      <h3 class="hcl-campaign-tweet-meter-lable">Tweet Meter</h3>
      <div class="tweet-meter-units"></div>
    </div>
    <div class="tweet-meter-lables">
      <?php for ($i = 8; $i > 0; $i--): ?>
        <div class="tweet-meter-lable cut-<?php echo $i; ?>"><?php print 'Cut ' . $i ?></div>
      <?php endfor ?>
    </div>
  </div>
  <?php if ($total_tweets_count): ?>
    <div class="total_tweets_count"><?php print $total_tweets_count ?></div>
  <?php endif; ?>
</div>
