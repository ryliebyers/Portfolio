import 'package:flutter/material.dart';



// Define dropdown options with mappings to asset file names

const Map<String, String> baseOptions = {
  'Select Base' : 'Base',
  'Skin 1': 'lib/assets/images/CharactersPNG/Base/Skin1.png',
  'Skin 2': 'lib/assets/images/CharactersPNG/Base/Skin2.png',
  'Skin 3': 'lib/assets/images/CharactersPNG/Base/Skin3.png',
  'Skin 4': 'lib/assets/images/CharactersPNG/Base/Skin4.png',
  'Skin 5': 'lib/assets/images/CharactersPNG/Base/Skin5.png',
  'Skin 6': 'lib/assets/images/CharactersPNG/Base/Skin6.png',
  'Skin 7': 'lib/assets/images/CharactersPNG/Base/Skin7.png',
};

const Map<String, String> headOptions = {
  'Select Head' : 'Hats',
  'Blue Mage Hood': 'lib/assets/images/CharactersPNG/Head/Blue_Mage_Hood.png',
  'Green Mage Hood': 'lib/assets/images/CharactersPNG/Head/Green_Mage_Hood.png',
  'Purple Mage Hood': 'lib/assets/images/CharactersPNG/Head/Purple_Mage_Hood.png',
  'Gold Diadem': 'lib/assets/images/CharactersPNG/Head/Dark_Crown.png',
  'Dark Crown': 'lib/assets/images/CharactersPNG/Head/Dark_Crown.png',
  'Golden Crown': 'lib/assets/images/CharactersPNG/Head/Golden_Crown.png',
  'Grey Mage Hood': 'lib/assets/images/CharactersPNG/Head/Hood.png',
  'Horns': 'lib/assets/images/CharactersPNG/Head/Horns.png',
  'Platinum Diadem': 'lib/assets/images/CharactersPNG/Head/Platinum_Diadem.png',
  'Red Mage Hood': 'lib/assets/images/CharactersPNG/Head/Red_Magee_Hood.png',
  'Silver Crown': 'lib/assets/images/CharactersPNG/Head/Silver_Crown.png',
  'Steel Diadem': 'lib/assets/images/CharactersPNG/Head/Steel_Diadem.png',
  'Steel Helmet 1': 'lib/assets/images/CharactersPNG/Head/Steel_Helmet.png',
  'Steel Helmet 2': 'lib/assets/images/CharactersPNG/Head/Steel_Helmet_2.png',

};

const Map<String, String> hairOptions = {
  'Select Hair' : 'Hair',
  'Black Ponytail': 'lib/assets/images/CharactersPNG/Hair/BlackPonytail.png',
  'Blonde Ponytail': 'lib/assets/images/CharactersPNG/Hair/BlondePonytail.png',
  'Light grey Ponytail': 'lib/assets/images/CharactersPNG/Hair/LightGrayPonytail.png',
  'Brown Ponytail': 'lib/assets/images/CharactersPNG/Hair/BrownPonytail.png',
  'Red Ponytail': 'lib/assets/images/CharactersPNG/Hair/TrueRedPonytail.png',
  'Curtain Black': 'lib/assets/images/CharactersPNG/Hair/CurtainHairBlack.png',
  'Curtain Blonde': 'lib/assets/images/CharactersPNG/Hair/CurtainHairBlonde.png',
  'Curtain Navy': 'lib/assets/images/CharactersPNG/Hair/CurtainHairDarkBlue.png',
  'Curtain Red': 'lib/assets/images/CharactersPNG/Hair/CurtainHairRed.png',
  'Curtain White': 'lib/assets/images/CharactersPNG/Hair/CurtainHairWhite.png',
  'Short Blonde': 'lib/assets/images/CharactersPNG/Hair/ShortBlonde.png',
  'Short Brown': 'lib/assets/images/CharactersPNG/Hair/ShortBrown.png',
  'Short Red': 'lib/assets/images/CharactersPNG/Hair/ShortRed.png',
  'Short Black': 'lib/assets/images/CharactersPNG/Hair/ShortBlack.png',
  'Long Brown': 'lib/assets/images/CharactersPNG/Hair/LongBrown.png',
  'Long Dark Brown': 'lib/assets/images/CharactersPNG/Hair/LongBlack.png',
  'Long BLack': 'lib/assets/images/CharactersPNG/Hair/DarkLongBrown.png',
  'Spike Red': 'Blib/assets/images/CharactersPNG/Hair/SpikeRed.png',
  'Spike Blue': 'lib/assets/images/CharactersPNG/Hair/BlueSpikedHair.png',
  'Spike Blonde': 'lib/assets/images/CharactersPNG/Hair/BlondeSpikedHair.png',
  'Black Spike': 'lib/assets/images/CharactersPNG/Hair/BlackSpikedHair.png',
  'Messy Long Black': 'lib/assets/images/CharactersPNG/Hair/MessyLongBlackHair.png',
  'Messy Long Red': 'lib/assets/images/CharactersPNG/Hair/MessyLongRedHair.png',
};

const Map<String, String> accessoriesOptions = {
  'Select Accessories' : 'Extras',
  'Back Bag': 'lib/assets/images/CharactersPNG/Accessories/BackBag.png',
  'Blue Cape': 'lib/assets/images/CharactersPNG/Accessories/BlueCape.png',
  'Green Cape': 'lib/assets/images/CharactersPNG/Accessories/GreenCape.png',
  'Red Cape': 'lib/assets/images/CharactersPNG/Accessories/RedCape.png',
  'Purple Cape': 'lib/assets/images/CharactersPNG/Accessories/PurpleCape.png',
  'Blue Scarf': 'lib/assets/images/CharactersPNG/Accessories/BlueScarf.png',
  'Red Scarf': 'lib/assets/images/CharactersPNG/Accessories/RedScarf.png',
  'Brown Scarf': 'lib/assets/images/CharactersPNG/Accessories/BrownScarf.png',
  'Blue Tabard': 'lib/assets/images/CharactersPNG/Accessories/BlueTabard.png',
  'Green Tabard': 'lib/assets/images/CharactersPNG/Accessories/GreenTabard.png',
  'Navy Tabard': 'lib/assets/images/CharactersPNG/Accessories/DarkBlueTabard.png',
  'Red Tabard': 'lib/assets/images/CharactersPNG/Accessories/RedTabard.png',
  'Yellow Tabard': 'lib/assets/images/CharactersPNG/Accessories/YellowTabard.png',
  'Lantern Tabard': 'lib/assets/images/CharactersPNG/Accessories/LanternTabardMark.png',
  'Glasses': 'lib/assets/images/CharactersPNG/Accessories/Glasses.png',
  'Ruby Necklace': 'lib/assets/images/CharactersPNG/Accessories/RubyNecklace.png',
  'Body Belt': 'lib/assets/images/CharactersPNG/Accessories/BodyBelt.png',
  'Alchemist Front Potions': 'lib/assets/images/CharactersPNG/Accessories/AlchemistFrontPotions.png',
  'Lantern': 'lib/assets/images/CharactersPNG/Accessories/Lantern.png',

};

const Map<String, String> earOptions = {
  'Select Ear' : 'Ears',
  'Elven Ear': 'lib/assets/images/CharactersPNG/Ear/ElvenEar.png',
  'Goblin Ear': 'lib/assets/images/CharactersPNG/Ear/GoblinEar.png',
  'Orc Ear': 'lib/assets/images/CharactersPNG/Ear/OrcEar.png',

};

const Map<String, String> eyebrowsOptions = {
  'Select Eyebrows' : 'Brows',
  'Black': 'lib/assets/images/CharactersPNG/Eyebrows/Black.png',
  'Red': 'lib/assets/images/CharactersPNG/Eyebrows/Red.png',
  'Blonde': 'lib/assets/images/CharactersPNG/Eyebrows/BlondeEyebrow.png',
  'Brown': 'lib/assets/images/CharactersPNG/Eyebrows/Brown2.png',
  'Light Grey': 'lib/assets/images/CharactersPNG/Eyebrows/LightGray.png',

};

const Map<String, String> eyesOptions = {
  'Select Eyes' : 'Eyes',
  'Brown': 'lib/assets/images/CharactersPNG/Eyes/Brown.png',
  'Pink 1': 'lib/assets/images/CharactersPNG/Eyes/Pink.png',
  'Pink 2': 'lib/assets/images/CharactersPNG/Eyes/pink2.png',
  'Dark Brown': 'lib/assets/images/CharactersPNG/Eyes/DarkBrown.png',
  'Light Blue': 'lib/assets/images/CharactersPNG/Eyes/LightBlue.png',
  'Light Green': 'lib/assets/images/CharactersPNG/Eyes/LightGreen.png',
  'Light Yellow': 'lib/assets/images/CharactersPNG/Eyes/LightYellow.png',
  'Red Scaly Yellow': 'lib/assets/images/CharactersPNG/Eyes/RedScalyYellowEyes.png',

};

const Map<String, String> equipmentOptions = {
  'Select Equipment' : 'Gear',
  'Lamp Shield': 'lib/assets/images/CharactersPNG/Equipment/LampShieldMark.png',
  'Sheathed Sword': 'lib/assets/images/CharactersPNG/Equipment/SheathedSword.png',
  'Shield In The Back': 'lib/assets/images/CharactersPNG/Equipment/Shieldintheback.png',
};

const Map<String, String> faceOptions = {
  'Select Face' : 'Face',
  'Orc': 'lib/assets/images/CharactersPNG/Face/Orc.png',
  'Old Beard': 'lib/assets/images/CharactersPNG/Face/OldBeard.png',
  'Black Beard': 'lib/assets/images/CharactersPNG/Face/BlackBeard.png',
  'Blonde Beard': 'lib/assets/images/CharactersPNG/Face/BlondeBeard.png',
  'Brown Beard': 'lib/assets/images/CharactersPNG/Face/BrownBeard.png',
  'Red Beard': 'lib/assets/images/CharactersPNG/Face/RedBeard.png',
  'Old Age': 'lib/assets/images/CharactersPNG/Face/OldAge.png',
  'Dragon Mouth': 'lib/assets/images/CharactersPNG/Face/DragonMouth.png',
  'Bear Scars': 'lib/assets/images/CharactersPNG/Face/OldBeard.png',
  'Purple War Paint': 'lib/assets/images/CharactersPNG/Face/PurpleWarPaint.png',
  'Blue War Paint': 'lib/assets/images/CharactersPNG/Face/BlueWarPaint.png',
  'Red War Paint': 'lib/assets/images/CharactersPNG/Face/RedWarPaint.png',

};

const Map<String, String> pantsOptions = {
  'Select Pants' : 'Pants',
  'Blue Trousers' : 'lib/assets/images/CharactersPNG/Pants/BlueTrousers.png',
  'Brown Trousers': 'lib/assets/images/CharactersPNG/Pants/BrownTrousers.png',
  'Blue Mage Trousers': 'lib/assets/images/CharactersPNG/Pants/BlueMageTrousers.png',
  'Green Mage Trousers': 'lib/assets/images/CharactersPNG/Pants/GreenMageTrousers.png',
  'Purple Mage Trousers': 'lib/assets/images/CharactersPNG/Pants/PurpleMageTrousers.png',
  'Red Mage Trousers': 'lib/assets/images/CharactersPNG/Pants/RedMageTrousers.png',
  'Red Trousers': 'lib/assets/images/CharactersPNG/Pants/RedTrousers.png',
  'Rusted Plate Pants': 'lib/assets/images/CharactersPNG/Pants/RustedPlatePants.png',
  'Plate Pants': 'lib/assets/images/CharactersPNG/Pants/PlatePants.png',

};

const Map<String, String> shirtsOptions = {
  'Select Shirts' : 'Shirts',
  'Chainmail': 'lib/assets/images/CharactersPNG/Shirts/Chainmail.png',
  'Breastplate': 'lib/assets/images/CharactersPNG/Shirts/Breastplate.png',
  'Rusted Breastplate': 'lib/assets/images/CharactersPNG/Shirts/RustedBreastplate.png',
  'Green Mage Robe': 'lib/assets/images/CharactersPNG/Shirts/GreenMageRobe.png',
  'Blue Mage Robe': 'lib/assets/images/CharactersPNG/Shirts/BlueMageRobe.png',
  'Purple Mage Robe': 'lib/assets/images/CharactersPNG/Shirts/PurpleMageRobe.png',
  'Red Mage Robe': 'lib/assets/images/CharactersPNG/Shirts/RedMageRobe.png',
  'Simple Brown Robe': 'lib/assets/images/CharactersPNG/Shirts/SimpleBrownRobe.png',
  'Black Noble Cloth': 'lib/assets/images/CharactersPNG/Shirts/BlackNobleCloth.png',
  'Blue Noble Cloth': 'lib/assets/images/CharactersPNG/Shirts/BlueNobleCloth.png',
  'Purple Noble Cloth': 'lib/assets/images/CharactersPNG/Shirts/PurpleNobleCloth.png',
  'Elven Simple Clothes': 'lib/assets/images/CharactersPNG/Shirts/ElvenSimpleClothes.png',
  'Green Noble Cloth': 'lib/assets/images/CharactersPNG/Shirts/GreenNobleCloth.png',
  'Simple Brown Clothes': 'lib/assets/images/CharactersPNG/Shirts/SimpleDarkBrownClothes.png',
  'Simple Light Brown Clothes': 'lib/assets/images/CharactersPNG/Shirts/SimpleLightBrownClothes.png',
  'Simple Purple Clothes': 'lib/assets/images/CharactersPNG/Shirts/SimplePurpleClothes.png',
  'Simple Yellow Clothes': 'lib/assets/images/CharactersPNG/Shirts/SimpleYellowClothes.png',
};

const Map<String, String> colorOptions = {
  'Background': 'Backdrop',
  'Pink': 'Pink',
  'Blue': 'Blue',
  'Black': 'Black',
  'White': 'White',
  'Green': 'Green',
  'Red': 'Red',
};
