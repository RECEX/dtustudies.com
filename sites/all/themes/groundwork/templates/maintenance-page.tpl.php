<?php

/**
 * @file
 * Groundwork theme implementation to display a single Drupal page while offline.
 *
 * All the available variables are mirrored in html.tpl.php and page.tpl.php.
 * Some may be blank but they are provided for consistency.
 *
 * @see template_preprocess()
 * @see template_preprocess_maintenance_page()
 */
?>
<!DOCTYPE html>
<html lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>">
<head>
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
  <?php print $scripts; ?>
  <!-- IE Fix for HTML5 Tags -->
  <!--[if lt IE 9]>
    <script src="http://html5shiv.googlecode.com/svn/trunk/html5.js"></script>
  <![endif]-->
</head>


<body class="<?php print $classes; ?>" <?php print $attributes;?>>

<div id="page-wrapper">
  <div id="page">



    <div id="skip-link">
      <a href="#main-content" class="element-invisible element-focusable"><?php print t('Skip to main content'); ?></a>
    </div>



    <header id="sector-header" class="noceda-sector">


      <div id="header-zone" class="noceda-zone-wrapper clearfix">
        <div id="header-section" class="container-24 noceda-section clearfix">
          <div id="header-section-inner" class="clearfix">

            <section id="branding" role="banner" class="noceda-region">

              <?php if ($logo): ?>
              <div id="logo-image">
                <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" id="logo" rel="home">
                  <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
                </a>
              </div><!-- /#logo-image -->
              <?php endif; ?>

              <?php if ($site_name || $site_slogan): ?>
              <div id="name-and-slogan">
                <hgroup>
                  <?php if ($site_name): ?>
                  <h1 id="site-name">
                    <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
                  </h1>
                  <?php endif; ?>
                  <?php if ($site_slogan): ?>
                  <h2 id="site-slogan"> <?php print $site_slogan; ?> </h2>
                  <?php endif; ?>
                </hgroup>
              </div><!-- /#name-and-slogan -->
              <?php endif; ?>

            </section><!-- /#branding -->

            <div id="header" class="noceda-region">
            </div><!-- /#header -->

          </div> <!-- /#header-section-inner -->
        </div> <!-- /#header-section -->
      </div> <!-- /#header-zone -->


    </header><!-- /#sector-header -->



    <section id="sector-content" class="noceda-sector">


      <div id="main-zone" class="noceda-zone">
        <div id="main" class="container-24 noceda-section clearfix">

          <div class="columns clearfix">

            <div id="main-content" role="main">
              <div id="main-content-inner" class="clearfix">

                <?php print $messages; ?>

                <?php if ($title): ?>
                  <h1 class="title" id="page-title"><?php print $title; ?></h1>
                <?php endif; ?>


                <?php if ($page['content']): ?>
                <div id="content">
                  <?php print $content; ?>
                </div> <!-- /#content -->
                <?php endif; ?>

              </div> <!-- /#main-content-inner -->
            </div> <!-- /#main-content -->

          </div>
        </div><!-- /#main -->
      </div> <!-- /#main-zone -->

    </section><!-- /#section-content -->


    <footer id="sector-footer" class="noceda-sector">

      <div id="footer-zone" class="noceda-zone-wrapper clearfix">
        <section id="footer-section" role="contentinfo" class="container-24 noceda-section clearfix">

          <?php if ($attribution): ?>
          <div id="attribution" class="noceda-region">
            <?php print $attribution; ?>
          </div>
          <?php endif; ?>

        </section><!-- /#footer-section -->
      </div> <!-- /#footer-zone -->

    </footer><!-- /#section-footer -->



  </div><!-- /#page -->
</div><!-- /#page-wrapper -->

</body>
</html>