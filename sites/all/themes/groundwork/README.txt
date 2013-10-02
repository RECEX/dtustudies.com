Welcome to Groundwork!

Groundwork documentation can be found at http://groundwork.noceda.no/handbook


INTRODUCTION
------------

What is Groundwork?

Groundwork is a theme framework. It was built to help you design beautiful
Drupal websites faster and more efficient. As its name implies, it's a
groundwork which comes already with sensible generic style defaults, CSS browser
hacks, collection of preset CSS classes and more. Because of Groundwork's basic
generic style, you may also wish to use it as is, as a structured minimalistic
theme.

Groundwork uses a 24-column grid system based on the 960.gs. Efficient layout
options available give endless possibilities, which makes the Groundwork suite
of themes extremely versatile. Customizing a website to specific layout and
design is very easy.

The Groundwork base theme supports 15 regions whereas the regions page_top,
page_bottom, and help are special hidden regions. The other 12 regions are
available to you for unlimited block placement and layout options via the Skinr
module.

Groundwork is not for everybody.
If you are a designer who wants to start everything from scratch, you may want
to take a look at the great and powerful starter themes available at drupal.org
like Zen, AdaptiveTheme, Fusion or Omega, to name a few.


FEATURES
--------

Here are the key features of Groundwork:

* HTML 5
* Web accessibility optimized with ARIA roles
* 24-column grid system based on 960.gs
* Supports one, two, and three-column layouts
* 15 regions with a special "Aside" region visible only in nodes.
* Optimized typography for all standard elements
* Advanced Theme Settings
* Powerful layout engine provides unlimited layout possibilities
* CSS Reset
* Collection of preset CSS classes
* HTML5 polyfill to support older browsers
* Formalize: HTML5 ready, progressively enhanced, cross-browser forms
* Icons for common Drupal form fields such as search, username, and password
  fields.
* and many more.


REQUIREMENTS
------------

1. Drupal (http://drupal.org/project/drupal)

2. Skinr (http://drupal.org/project/skinr)


INSTALLATION
------------

  1. Download Groundwork from http://drupal.org/project/groundwork

  2. Extract the downloaded file and place the groundwork folder of your Drupal
     installation under one of the following locations:
       sites/all/themes
       sites/default/themes
       sites/example.com/themes

       (Please check http://drupal.org/getting-started/install-contrib/themes
       for more information on these folders)

  3. It is highly recommended to create a sub-theme instead of enabling
     Groundwork. Please see Alternatives #2, #3 and #4 below for more info.

     Alternative 1: Enable Groundwork (not recommended)
       1. Log in as admin in your Drupal installation and go to
          Administration > Appearance > List
          (http://example.com/admin/appearance/list)
          Click the "Enable and set default" link below the theme's description.
       2. Copy and rename local-blank.css to local.css found on the css folder.
          This is where you will put all your customizations.
       Note: You do not need to add "css/local.css" to the .info file.
       Groundwork will try to find local.css and use it if it's available.

     Alternative 2: Automagically create a sub-theme using Drush.
       1. Create a new subtheme
          $ drush groundwork 'Human-friendly Theme Name' machinename
       Help in creating a sub-theme is available...
       $ drush help groundwork
       Note: The drush script assumes that Groundwork resides in sites/all/themes

     Alternative 3. Create your own subtheme using CustomWork
       1. Copy the folder "CustomWork" to your theme folder
       2. Rename the folder "CustomWork" to the machine-name of your theme.
       3. Rename CustomWork.info.txt to the same name of your folder and
          remove .txt.
       4. Edit CustomWork.info and find "name = CustomWork". This is the
          human-friendly name of your theme. Change it to your desired theme
          name with the first letter capitalized.
       5. Find and replace all "CustomWork" in theme-settings.php and
          template.php
       Note: It is not necessary to enable Groundwork if you are going to use a
       sub-theme.

     Alternative 4. Use an existing sub-theme.
       1. Look for a Groundwork sub-theme which looks the nearest you want to
          achieve with your site design. Download and install it.
       2. Rename local-blank.css of your sub-theme to local.css. This is where
          you will put all your customizations.
       Note: It is not necessary to enable Groundwork if you are going to use a
       sub-theme.

Further Reading:
  Learn more about sub-theming: http://drupal.org/node/225125
  Learn more about general Drupal theming in the Drupal theme guide:
    http://drupal.org/theme-guide


TODO
----

- Icons: Provide icons for common Drupal blocks.


ACKNOWLEDGMENTS
---------------

Thanks to:

  the awesome contributed Drupal starter themes available at
  http://drupal.org/project/themes and their great theme developers
  for the inspiration and ideas.

  Nathan Smith for coming up with a great grid system. (960.gs)

  the great graphic artists who contributed their GPL icons to the
  Open Icon Library (http://openiconlibrary.sourceforge.net)

  the Formalize project at http://formalize.me/ for providing with an
  awesome CSS framework for forms.



Thanks for downloading the Groundwork Framework and I hope that you find it useful
for your needs.

John Noceda (JohnNoc)
