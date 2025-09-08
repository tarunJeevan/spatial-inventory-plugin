# Spatial Inventory Plugin
A customizable spatial inventory that can be added to any 2D or 3D game. Written primarily in C++ with Blueprints to customize and extend the system in a designer-friendly way.

## Usage
Enable the plugin by going to Edit->Plugins, search for 'Spatial Inventory', and ensure the checkbox is checked. Within the plugin folder, you will find all necessary Blueprints and data assets. Below are some of steps needed to make full use of the plugin.

#### Item Icons
To use icons for your items (which will appear in the inventory grid once picked up), follow the steps below:
1. Add the icon PNGs to the ItemIcons folder (either import them or drag them into the Content Browser or copy them into the folder in the File Explorer)
2. Select all added PNGs and right-click to open the properties menu. Go to 'Asset Actions->Bulk Edit via Property Matrix'.
3. For all icon PNGs, ensure the following options are set:
  - Under 'Level of Detail', change the 'Texture Group' to 'UI'.
  - Under 'Compression', change 'Compression Setting' to 'UserInterface2D(RGBA)'.
  - Save all changes before exiting.
