<!-- #header -->
<div id="header">
	<!-- #header-inside -->
    <div id="header-inside" class="container_12 clearfix">
    	<!-- #header-inside-left -->
        <div id="header-inside-left" class="grid_8">
            
            <?php if ($logo): ?>
            <a href="<?php print check_url($front_page); ?>" title="<?php print t('Home'); ?>"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" /></a>
            <?php endif; ?>
     
            <?php if ($site_name || $site_slogan): ?>
            <div class="clearfix">
            <?php if ($site_name): ?>
            <span id="site-name"><a href="<?php print check_url($front_page); ?>" title="<?php print t('Home'); ?>"><?php print $site_name; ?></a></span>
            <?php endif; ?>
            <?php if ($site_slogan): ?>
            <span id="slogan"><?php print $site_slogan; ?></span>
            <?php endif; ?>
            </div>
            <?php endif; ?>
            
        </div><!-- EOF: #header-inside-left -->
        
        <!-- #header-inside-right -->    
        <div id="header-inside-right" class="grid_4">

			<?php print render($page['search_area']); ?>

        </div><!-- EOF: #header-inside-right -->
    
    </div><!-- EOF: #header-inside -->

</div><!-- EOF: #header -->

<!-- #header-menu -->
<div id="header-menu">
	<!-- #header-menu-inside -->
    <div id="header-menu-inside" class="container_12 clearfix">
    
    	<div class="grid_12">
            <div id="navigation" class="clearfix">
            <?php if ($page['navigation']) :?>
            <?php print drupal_render($page['navigation']); ?>
            <?php else :
            if (module_exists('i18n_menu')) {
            $main_menu_tree = i18n_menu_translated_tree(variable_get('menu_main_links_source', 'main-menu'));
            } else {
            $main_menu_tree = menu_tree(variable_get('menu_main_links_source', 'main-menu')); 
            }
            print drupal_render($main_menu_tree);
            endif; ?>
            </div>
        </div>
        
    </div><!-- EOF: #header-menu-inside -->

</div><!-- EOF: #header-menu -->

<!-- #banner -->
<div id="banner">

	<?php print render($page['banner']); ?>
	
    <?php if (theme_get_setting('slideshow_display','corporateclean')): ?>
    
    <?php if ($is_front): ?>
    
    <!-- #slideshow -->
    <div id="slideshow">
        
        
        <!--slider-item-->
        <div class="slider-item">
            <div class="content container_12">
            	<div class="grid_12">
                
                <!--slider-item content-->
                <h2>NOTESMART</h2>
                <br/>
                <div class="field-item even" property="content:encoded"><p>DTU | Studies brings to you <strong>NOTESMART</strong>, the ultimate replacement for all the study-material sharing blogs.</p>
<p><strong>NOTESMART</strong> is a repository of class notes, lecture transcripts, lab manuals, question papers, ebook extracts and various other study materials, which will not just help, but become a necessity during studies.<br><em>But NOTESMART is not just that. There's more to it</em><br>
NOTESMART also makes it possible for <strong>you</strong> - the user, to share your own notes and study materials with everyone else via our repository. You get due credit and recognition for notes that you have uploaded.</p>
<div class="buttons">
 <a href="notesmart/share"><input value="Share Notes" type="button"></a> <a href="notesmart/download"><input value="Download Notes" type="button"></a>
</div>
</div>
                <!--EOF:slider-item content-->
                
				</div>
            </div>
        </div>
        <!--EOF:slider-item-->
        

        <!--slider-item-->
        <div class="slider-item">
            <div class="content container_12">
            	<div class="grid_12">
                
                <!--slider-item content-->
                <h2>BOOKBAZAR</h2>
                <br/>
                <div class="field-item even" property="content:encoded"><p>Have old books to sell ? Want to buy used books ? This is the place you are looking for !<br>
No middlemen, No charges. Advertise your books, get contacted, sell them. All the money is yours.</p>
<p>Create a listing for books you want to sell and wait untill someone contacts you. Once you have sold the book, please remeber to edit your listing from "Active" to "Disabled".</p>
<div class="buttons">
 <a href="bookbazar/add-book?destination=bookbazar/books-on-sale"><input value="Add Book to sell" type="button"></a> <a href="bookbazar/books-for-sale"><input value="View Books on Sale" type="button"></a>
</div>
<p><font color="red">NOTE: BookBazar is available only for registered users. If the listings are not visible, please login via Facebook</font></p>
</div>
                <!--EOF:slider-item content-->
                
				</div>
            </div>
        </div>
        <!--EOF:slider-item-->

    
    </div>
    <!-- EOF: #slideshow -->
    
    <!-- #slider-controls-wrapper -->
    <div id="slider-controls-wrapper">
        <div id="slider-controls" class="container_12">
            <ul id="slider-navigation">
                <li><a href="#"></a></li>
                <li><a href="#"></a></li>
                
            </ul>
        </div>
    </div>
    <!-- EOF: #slider-controls-wrapper -->
    
    <?php endif; ?>
    
	<?php endif; ?>  

</div><!-- EOF: #banner -->


<!-- #content -->
<div id="content">
	<!-- #content-inside -->
    <div id="content-inside" class="container_12 clearfix">
    
        <?php if ($page['sidebar_first']) :?>
        <!-- #sidebar-first -->
        <div id="sidebar-first" class="grid_4">
        	<?php print render($page['sidebar_first']); ?>
        </div><!-- EOF: #sidebar-first -->
        <?php endif; ?>
        
        <?php if ($page['sidebar_first'] && $page['sidebar_second']) { ?>
        <div class="grid_4">
        <?php } elseif ($page['sidebar_first'] || $page['sidebar_second']) { ?>
        <div id="main" class="grid_8">
		<?php } else { ?>
        <div id="main" class="grid_12">    
        <?php } ?>
            
            <?php if (theme_get_setting('breadcrumb_display','corporateclean')): print $breadcrumb; endif; ?>
            
            <?php if ($page['highlighted']): ?><div id="highlighted"><?php print render($page['highlighted']); ?></div><?php endif; ?>
       
            <?php if ($messages): ?>
            <div id="console" class="clearfix">
            <?php print $messages; ?>
            </div>
            <?php endif; ?>
     
            <?php if ($page['help']): ?>
            <div id="help">
            <?php print render($page['help']); ?>
            </div>
            <?php endif; ?>
            
            <?php if ($action_links): ?>
            <ul class="action-links">
            <?php print render($action_links); ?>
            </ul>
            <?php endif; ?>
            
			<?php print render($title_prefix); ?>
            <?php if ($title): ?>
            <h1><?php print $title ?></h1>
            <?php endif; ?>
            <?php print render($title_suffix); ?>
            
            <?php if ($tabs): ?><?php print render($tabs); ?><?php endif; ?>
            
            <?php print render($page['content']); ?>
            
            <?php print $feed_icons; ?>
            
        </div><!-- EOF: #main -->
        
        <?php if ($page['sidebar_second']) :?>
        <!-- #sidebar-second -->
        <div id="sidebar-second" class="grid_4">
        	<?php print render($page['sidebar_second']); ?>
        </div><!-- EOF: #sidebar-second -->
        <?php endif; ?>  

    </div><!-- EOF: #content-inside -->

</div><!-- EOF: #content -->

<!-- #footer -->    
<div id="footer">
	<!-- #footer-inside -->
    <div id="footer-inside" class="container_12 clearfix">
    
        <div class="footer-area grid_4">
        <?php print render($page['footer_first']); ?>
        </div><!-- EOF: .footer-area -->
        
        <div class="footer-area grid_4">
        <?php print render($page['footer_second']); ?>
        </div><!-- EOF: .footer-area -->
        
        <div class="footer-area grid_4">
        <?php print render($page['footer_third']); ?>
        </div><!-- EOF: .footer-area -->
       
    </div><!-- EOF: #footer-inside -->

</div><!-- EOF: #footer -->

<!-- #footer-bottom -->    
<div id="footer-bottom">

	<!-- #footer-bottom-inside --> 
    <div id="footer-bottom-inside" class="container_12 clearfix">
    	<!-- #footer-bottom-left --> 
    	<div id="footer-bottom-left" class="grid_8">
        
            <?php print theme('links__system_secondary_menu', array('links' => $secondary_menu, 'attributes' => array('class' => array('secondary-menu', 'links', 'clearfix')))); ?>
            
            <?php print render($page['footer']); ?>
            
        </div>
    	<!-- #footer-bottom-right --> 
        <div id="footer-bottom-right" class="grid_4">
        
        	<?php print render($page['footer_bottom_right']); ?>
        
        </div><!-- EOF: #footer-bottom-right -->
       
    </div><!-- EOF: #footer-bottom-inside -->
    
    <!-- #credits -->   
    <div id="credits" class="container_12 clearfix">
        <div class="grid_12">
        <p> Copyright (c) <?php echo date("Y"); ?> RecEx, DTU </p>
        </div>
    </div>
    <!-- EOF: #credits -->

</div><!-- EOF: #footer -->
