<?php

/**
* @file
* Groundwork Theme's implementation to display a single Drupal page.
*
* Available variables:
*
* General utility variables:
* - $base_path: The base URL path of the Drupal installation. At the very
*   least, this will always default to /.
* - $directory: The directory the template is located in, e.g. modules/system
*   or themes/bartik.
* - $is_front: TRUE if the current page is the front page.
* - $logged_in: TRUE if the user is registered and signed in.
* - $is_admin: TRUE if the user has permission to access administration pages.
*
* Site identity:
* - $front_page: The URL of the front page. Use this instead of $base_path,
*   when linking to the front page. This includes the language domain or
*   prefix.
* - $logo: The path to the logo image, as defined in theme configuration.
* - $site_name: The name of the site, empty when display has been disabled
*   in theme settings.
* - $site_slogan: The slogan of the site, empty when display has been disabled
*   in theme settings.
*
* Navigation:
* - $main_menu (array): An array containing the Main menu links for the
*   site, if they have been configured.
* - $secondary_menu (array): An array containing the Secondary menu links for
*   the site, if they have been configured.
* - $breadcrumb: The breadcrumb trail for the current page.
*
* Page content (in order of occurrence in the default page.tpl.php):
* - $title_prefix (array): An array containing additional output populated by
*   modules, intended to be displayed in front of the main title tag that
*   appears in the template.
* - $title: The page title, for use in the actual HTML content.
* - $title_suffix (array): An array containing additional output populated by
*   modules, intended to be displayed after the main title tag that appears in
*   the template.
* - $messages: HTML for status and error messages. Should be displayed
*   prominently.
* - $tabs (array): Tabs linking to any sub-pages beneath the current page
*   (e.g., the view and edit tabs when displaying a node).
* - $action_links (array): Actions local to the page, such as 'Add menu' on the
*   menu administration interface.
* - $feed_icons: A string of all feed icons for the current page.
* - $node: The node object, if there is an automatically-loaded node
*   associated with the page, and the node ID is the second argument
*   in the page's path (e.g. node/12345 and node/12345/revisions, but not
*   comment/reply/12345).
*
* Regions:
* - $page['help']: Dynamic help text, mostly for admin pages.
* - $page['topbar']: Items for the topbar region.
* - $page['content']: The main content of the current page.
* - $page['sidebar_first']: Items for the first sidebar.
* - $page['sidebar_second']: Items for the second sidebar.
* - $page['header']: Items for the header region.
* - $page['footer']: Items for the footer region.
*
* @see template_preprocess()
* @see template_preprocess_page()
* @see template_process()
*/
?>
<div id="page-wrapper">
  <div id="page">



    <div id="skip-link">
      <a href="#main-content" class="element-invisible element-focusable"><?php print t('Skip to main content'); ?></a>
      <?php if ($main_menu): ?>
      <a href="#main-navigation" class="element-invisible element-focusable"><?php print t('Skip to navigation'); ?></a>
      <?php endif; ?>
    </div>



    <header id="sector-header" class="noceda-sector">


      <?php if ($page['topbar']): ?>
      <div id="topbar-zone" class="noceda-zone-wrapper clearfix">
        <section id="topbar-section" class="container-24 noceda-section clearfix">

          <div id="topbar" class="noceda-region">
            <?php print render($page['topbar']); ?>
          </div>

        </section><!-- /#topbar-section -->
      </div><!-- /#topbar-zone -->
      <?php endif; ?>


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
              <?php print render($page['header']); ?>
            </div><!-- /#header -->

          </div> <!-- /#header-section-inner -->
        </div> <!-- /#header-section -->
      </div> <!-- /#header-zone -->


      <?php if ($main_menu || $page['navigation']): ?>
      <div id="navbar-zone" class="noceda-zone-wrapper clearfix">
        <div id="navbar-section" class="container-24 noceda-section clearfix">

          <?php if ($page['navigation']): ?>
          <div id="main-navigation" role="navigation" class="noceda-region clearfix">
            <?php print render($page['navigation']); ?>
          </div><!-- /#main-navigation -->
          <?php else: ?>
          <nav id="main-navigation" role="navigation" class="noceda-region clearfix">
            <?php print theme('links__system_main_menu', array(
              'links' => $main_menu,
              'attributes' => array(
                'id' => 'main-menu',
                'class' => array('links', 'clearfix'),
              ),
              'heading' => array(
                'text' => t('Main menu'),
                'level' => 'h2',
                'class' => array('element-invisible'),
              ),
            )); ?>
          </nav><!-- /#main-navigation -->
          <?php endif; ?>

        </div><!-- /#navbar-section -->
      </div><!-- /#navbar-zone -->
      <?php endif; ?>


    </header><!-- /#sector-header -->



    <section id="sector-content" class="noceda-sector">


      <div id="main-zone" class="noceda-zone">
        <div id="main" class="container-24 noceda-section clearfix">

          <?php if ($page['billboard']): ?>
          <div id="billboard" class="noceda-region clearfix">
            <?php print render($page['billboard']); ?>
          </div>
          <?php endif; ?>

          <?php if ($page['highlighted']): ?>
          <div id="highlighted" class="noceda-region clearfix">
            <?php print render($page['highlighted']); ?>
          </div>
          <?php endif; ?>

          <div class="columns clearfix">

            <div id="main-content" role="main">
              <div id="main-content-inner" class="clearfix">

                <?php print $breadcrumb; ?>

                <?php print $messages; ?>

                <?php print render($title_prefix); ?>
                <?php if ($title): ?>
                  <h1 class="title" id="page-title"><?php print $title; ?></h1>
                <?php endif; ?>
                <?php print render($title_suffix); ?>

                <?php if (!empty($tabs['#primary'])): ?>
                  <div class="tabs-wrapper clearfix"><?php print render($tabs); ?></div>
                <?php endif; ?>

                <?php print render($page['help']); ?>

                <?php if ($action_links): ?>
                  <ul class="action-links"><?php print render($action_links); ?></ul>
                <?php endif; ?>

                <?php if ($page['content']): ?>
                <div id="content">
                  <?php print render($page['content']); ?>
                </div> <!-- /#content -->
                <?php endif; ?>

              </div> <!-- /#main-content-inner -->
            </div> <!-- /#main-content -->

            <?php if ($page['sidebar_first']): ?>
            <aside id="sidebar-first" class="sidebar" role="complementary">
              <?php print render($page['sidebar_first']); ?>
            </aside> <!-- /#sidebar-first -->
            <?php endif; ?>

            <?php if ($page['sidebar_second']): ?>
            <aside id="sidebar-second" class="sidebar" role="complementary">
              <?php print render($page['sidebar_second']); ?>
            </aside> <!-- /#sidebar-second -->
            <?php endif; ?>

          </div>
        </div><!-- /#main -->
      </div> <!-- /#main-zone -->

    </section><!-- /#section-content -->



    <?php if ($page['appendix'] || $page['supplement']): ?>
    <section id="sector-extras" class="noceda-sector">


      <?php if ($page['appendix']): ?>
      <div id="appendix-zone" class="noceda-zone-wrapper clearfix">
        <div id="appendix-section" class="container-24 noceda-section clearfix">
          <div id="appendix" class="noceda-region">
            <?php print render($page['appendix']); ?>
          </div>
        </div>
      </div> <!-- /#appendix-zone -->
      <?php endif; ?>


      <?php if ($page['supplement']): ?>
      <div id="supplement-zone" class="noceda-zone-wrapper clearfix">
        <div id="supplement-section" class="container-24 noceda-section clearfix">
          <div id="supplement" class="noceda-region">
            <?php print render($page['supplement']); ?>
          </div>
        </div>
      </div> <!-- /#supplement-zone -->
      <?php endif; ?>


    </section><!-- /#section-extras -->
    <?php endif; ?>



    <footer id="sector-footer" class="noceda-sector">

      <div id="footer-zone" class="noceda-zone-wrapper clearfix">
        <section id="footer-section" role="contentinfo" class="container-24 noceda-section clearfix">

          <?php if ($page['footer']): ?>
          <div id="footer" class="noceda-region">
            <?php print render($page['footer']); ?>
          </div>
          <?php endif; ?>

          <?php if ($secondary_menu): ?>
          <nav id="secondary-navigation" role="navigation" class="noceda-region clearfix">
            <?php print theme('links__system_secondary_menu', array(
              'links' => $secondary_menu,
              'attributes' => array(
              'id' => 'secondary-menu',
              'class' => array('links', 'inline', 'clearfix'),
              ),
              'heading' => array(
              'text' => t('Secondary menu'),
              'level' => 'h2',
              'class' => array('element-invisible'),
              ),
            )); ?>
          </nav> <!-- /#secondary-navigation -->
          <?php endif; ?>

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