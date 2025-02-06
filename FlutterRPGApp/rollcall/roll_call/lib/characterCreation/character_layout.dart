import 'package:flutter/material.dart';
import 'character_customization.dart';
import 'package:firebase_core/firebase_core.dart';
import 'character_customization.dart';
import 'characterdisplay.dart';
import 'package:firebase_auth/firebase_auth.dart';
import 'package:cloud_firestore/cloud_firestore.dart';
import 'package:uuid/uuid.dart';
import 'character_customization.dart';



// void main() async {
//   WidgetsFlutterBinding.ensureInitialized();
//   await Firebase.initializeApp(); // Initialize Firebase
//   runApp(CharacterSheetApp());
// }

// class CharacterSheetApp extends StatelessWidget {
//   @override
//   Widget build(BuildContext context) {
//     return MaterialApp(
//       title: 'Character Sheet',
//       theme: ThemeData(primarySwatch: Colors.blue),
//       home: CharacterSheetForm(),
//     );
//   }
// }

class CharacterSheetForm extends StatefulWidget {

    final String gameID;
    const  CharacterSheetForm({required this.gameID, Key? key}) : super(key: key);

  @override
  _CharacterSheetFormState createState() => _CharacterSheetFormState();
}




class _CharacterSheetFormState extends State<CharacterSheetForm> {
  final _formKey = GlobalKey<FormState>();

  // Controllers for Basic Information
  final TextEditingController nameController = TextEditingController();
  final TextEditingController classController = TextEditingController();
  final TextEditingController raceController = TextEditingController();
  final TextEditingController backgroundController = TextEditingController();
  final TextEditingController ageController = TextEditingController();
  final TextEditingController genderController = TextEditingController();
  final TextEditingController alignmentController = TextEditingController();
  final TextEditingController playerNameController = TextEditingController();

  // Attributes/Abilities
  Map<String, TextEditingController> attributes = {
    "Strength (STR)": TextEditingController(),
    "Dexterity (DEX)": TextEditingController(),
    "Constitution (CON)": TextEditingController(),
    "Intelligence (INT)": TextEditingController(),
    "Wisdom (WIS)": TextEditingController(),
    "Charisma (CHA)": TextEditingController(),
  };

  // Dynamic Lists
  List<Map<String, String>> skills = []; // Map for skill name and level/bonus
  Map<String, TextEditingController> combatStats = {
    "Hit Points (HP)": TextEditingController(),
    "Armor Class (AC)": TextEditingController(),
    "Initiative Bonus": TextEditingController(),
    "Attack Bonus (Melee/Ranged)": TextEditingController(),
    "Damage (Melee/Ranged)": TextEditingController(),
    "Special Abilities": TextEditingController(),
  };
  List<String> weapons = [];
  List<String> armor = [];
  List<String> gear = [];
  List<String> magicItems = [];
  List<Map<String, String>> spells = []; // Map for spell name, description, and usage

  // Background & Personal Details
  final TextEditingController backstoryController = TextEditingController();
  final TextEditingController personalityTraitsController = TextEditingController();
  final TextEditingController goalsController = TextEditingController();
  final TextEditingController alliesController = TextEditingController();
  final TextEditingController enemiesController = TextEditingController();

  // Notes & Miscellaneous
  List<String> quests = [];
  List<String> locations = [];
  List<String> events = [];
  final TextEditingController notesController = TextEditingController();

  @override
  void dispose() {
    // Dispose all controllers
    nameController.dispose();
    classController.dispose();
    raceController.dispose();
    backgroundController.dispose();
    ageController.dispose();
    genderController.dispose();
    alignmentController.dispose();
    playerNameController.dispose();
    attributes.values.forEach((controller) => controller.dispose());
    combatStats.values.forEach((controller) => controller.dispose());
    backstoryController.dispose();
    personalityTraitsController.dispose();
    goalsController.dispose();
    alliesController.dispose();
    enemiesController.dispose();
    notesController.dispose();
    super.dispose();
  }

void _addDynamicItem<T>(List<T> list, T item) {
  setState(() {
    list.add(item);
  });
}

  void _removeDynamicItem(List list, int index) {
    setState(() {
      list.removeAt(index);
    });
  }

  Future<void> _submitCharacterData() async {
    if (_formKey.currentState!.validate()) {
      final userId = FirebaseAuth.instance.currentUser?.uid;
      if (userId == null) {
        print("User not logged in");
        return;
      }

      final characterData = {
        "basicInfo": {
          "name": nameController.text,
          "class": classController.text,
          "race": raceController.text,
          "background": backgroundController.text,
          "age": ageController.text,
          "gender": genderController.text,
          "alignment": alignmentController.text,
          "playerName": playerNameController.text,
        },
        "attributes": attributes.map((key, controller) => MapEntry(key, controller.text)),
        "skills": skills,
        "combatStats": combatStats.map((key, controller) => MapEntry(key, controller.text)),
        "equipment": {
          "weapons": weapons,
          "armor": armor,
          "gear": gear,
          "magicItems": magicItems,
        },
        "spells": spells,
        "backgroundDetails": {
          "backstory": backstoryController.text,
          "personalityTraits": personalityTraitsController.text,
          "goals": goalsController.text,
          "allies": alliesController.text,
          "enemies": enemiesController.text,
        },
        "notes": {
          "quests": quests,
          "locations": locations,
          "events": events,
          "miscellaneous": notesController.text,
        },
      };

      try {
        await FirebaseFirestore.instance
            .collection("users")
            .doc(userId)
            .collection("games")
            .doc(widget.gameID)
            .set({"characterData": characterData}, SetOptions(merge: true));

        print("Character data saved successfully");
        Navigator.push(
          context,
          MaterialPageRoute(
            builder: (context) => CharacterDisplayScreen(userId: userId, gameID: widget.gameID),
          ),
        );
      } catch (e) {
        print("Error saving character data: $e");
      }
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: Text('Character Sheet')),
body: Container(
      decoration: BoxDecoration(
        image: DecorationImage(
          image: AssetImage('lib/assets/images/backgrounds/darkgreen.png'), // Path to your image
          fit: BoxFit.cover, // Ensures the image covers the entire screen
        ),
      ),



      
      child: SingleChildScrollView(
        padding: EdgeInsets.all(16.0),
        child: Form(
          key: _formKey,
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              _buildSection('Basic Information', _buildBasicInfoSection()),
              _buildSection('Attributes/Abilities', _buildAttributesSection()),
              _buildSection('Skills', _buildSkillsSection()),
              _buildSection('Combat Stats', _buildCombatStatsSection()),
              _buildSection('Equipment', _buildEquipmentSection()),
              _buildSection('Spells/Powers', _buildSpellsSection()),
              _buildSection('Background & Personal Details', _buildBackgroundDetailsSection()),
              _buildSection('Notes & Miscellaneous', _buildNotesSection()),
              SizedBox(height: 20),
ElevatedButton(
  onPressed: _submitCharacterData,
  child: Text('Submit'),
  style: ElevatedButton.styleFrom(
    backgroundColor: const Color.fromARGB(255, 255, 255, 255), // Background color
    foregroundColor: Color.fromRGBO(255, 215, 0, 1.0), // Text color (gold)
  ),
),              
            ],
          ),
        ),
      ),
),
    );
  }

  Widget _buildSection(String title, Widget content) {
    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Text(title, style: TextStyle(fontSize: 20, fontWeight: FontWeight.bold, color: Colors.white)),
        SizedBox(height: 10),
        content,
        Divider(thickness: 2, color: Colors.white),
      ],
    );
  }

  Widget _buildBasicInfoSection() {
    return Column(
      children: [
        _buildTextField(nameController, 'Name'),
        _buildTextField(classController, 'Class/Profession'),
        _buildTextField(raceController, 'Race/Species'),
        _buildTextField(backgroundController, 'Background/Origin'),
        _buildTextField(ageController, 'Age', keyboardType: TextInputType.number),
        _buildTextField(genderController, 'Gender'),
        _buildTextField(alignmentController, 'Alignment'),
        _buildTextField(playerNameController, 'Player Name'),
      ],
    );
  }

  Widget _buildAttributesSection() {
    return Column(
      children: attributes.entries.map((entry) {
        return _buildTextField(entry.value, entry.key, keyboardType: TextInputType.number);
      }).toList(),
    );
  }

  Widget _buildSkillsSection() {
    return Column(
      children: [
        ...skills.asMap().entries.map((entry) {
          final index = entry.key;
          final skill = entry.value;
          return Row(
            children: [
              Expanded(child: _buildTextFieldForSkill(skill, index)),
              IconButton(icon: Icon(Icons.remove, color: Colors.white), onPressed: () => _removeDynamicItem(skills, index)),
            ],
          );
        }).toList(),
        ElevatedButton(onPressed: () => _addDynamicItem(skills, {'Skill Name': '', 'Level/Bonus': ''}), child: Text('Add Skill')),
      ],
    );
  }

  Widget _buildTextFieldForSkill(Map<String, String> skill, int index) {
    return Column(
      children: [
        TextFormField(
          decoration: InputDecoration(labelText: 'Skill Name ${index + 1}'),
          initialValue: skill['Skill Name'],
          onChanged: (value) => setState(() => skill['Skill Name'] = value),
          style: TextStyle(color: Colors.white),
        ),
        TextFormField(
          decoration: InputDecoration(labelText: 'Level/Bonus'),
          initialValue: skill['Level/Bonus'],
          onChanged: (value) => setState(() => skill['Level/Bonus'] = value),
          style: TextStyle(color: Colors.white),
        ),
      ],
    );
  }

  Widget _buildCombatStatsSection() {
    return Column(
      children: combatStats.entries.map((entry) {
        return _buildTextField(entry.value, entry.key, keyboardType: TextInputType.number);
      }).toList(),
    );
  }

  Widget _buildEquipmentSection() {
    return Column(
      children: [
        _buildDynamicList(weapons, 'Weapons'),
        _buildDynamicList(armor, 'Armor'),
        _buildDynamicList(gear, 'Gear/Items'),
        _buildDynamicList(magicItems, 'Magic Items'),
      ],
    );
  }

  Widget _buildDynamicList(List<String> list, String label) {
    return Column(
      children: [
        ...list.asMap().entries.map((entry) {
          final index = entry.key;
          return Row(
            children: [
              Expanded(
                child: TextFormField(
                 initialValue: list[index],
                  decoration: InputDecoration(labelText: '$label ${index + 1}'),
                  onChanged: (value) => setState(() => list[index] = value),
                ),
              ),
              IconButton(icon: Icon(Icons.remove), onPressed: () => _removeDynamicItem(list, index)),
            ],
          );
        }).toList(),
        ElevatedButton(onPressed: () => _addDynamicItem(list, ''), child: Text('Add $label')),
      ],
    );
  }

  Widget _buildSpellsSection() {
    return Column(
      children: [
        ...spells.asMap().entries.map((entry) {
          final index = entry.key;
          final spell = entry.value;
          return Column(
            children: [
              TextFormField(
                
                decoration: InputDecoration(labelText: 'Spell Name ${index + 1}'),
                initialValue: spell['Spell Name'],
                onChanged: (value) => setState(() => spell['Spell Name'] = value),
              ),
              TextFormField(
                decoration: InputDecoration(labelText: 'Description'),
                initialValue: spell['Description'],
                onChanged: (value) => setState(() => spell['Description'] = value),
              ),
              TextFormField(
                decoration: InputDecoration(labelText: 'Usage'),
                initialValue: spell['Usage'],
                onChanged: (value) => setState(() => spell['Usage'] = value),
              ),
              IconButton(icon: Icon(Icons.remove, color: Colors.white), onPressed: () => _removeDynamicItem(spells, index)),
            ],
          );
        }).toList(),
        ElevatedButton(
            onPressed: () => _addDynamicItem(spells, {'Spell Name': '', 'Description': '', 'Usage': ''}),
            child: Text('Add Spell')),
      ],
    );
  }

  Widget _buildBackgroundDetailsSection() {
    return Column(
      children: [
        _buildTextField(backstoryController, 'Backstory'),
        _buildTextField(personalityTraitsController, 'Personality Traits'),
        _buildTextField(goalsController, 'Goals'),
        _buildTextField(alliesController, 'Allies'),
        _buildTextField(enemiesController, 'Enemies'),
      ],
    );
  }

  Widget _buildNotesSection() {
    return Column(
      children: [
        _buildDynamicList(quests, 'Quests'),
        _buildDynamicList(locations, 'Locations'),
        _buildDynamicList(events, 'Events'),
        _buildTextField(notesController, 'Miscellaneous Notes'),
      ],
    );
  }

  // Widget _buildTextField(TextEditingController controller, String label,
  //     {TextInputType keyboardType = TextInputType.text}) {
  //   return TextFormField(
  //     controller: controller,
  //     decoration: InputDecoration(  labelText: label,
  //     labelStyle: TextStyle(color: Colors.white), // Label text color
  //     filled: true, // Optional: to give a background color to the text field
  //     fillColor: Colors.black.withOpacity(0.5),),
      
  //     keyboardType: keyboardType,
      

    
      
  //     style: TextStyle(color: Colors.white),
  //     validator: (value) => value!.isEmpty ? '$label cannot be empty' : null,
  //      cursorColor: Color.fromRGBO(255, 215, 0, 1.0), // Custom gold cursor color
  //   );
  // }

  Widget _buildTextField(TextEditingController controller, String label, {TextInputType keyboardType = TextInputType.text}) {
  return TextFormField(
    controller: controller,
    decoration: InputDecoration(
      labelText: label,
      labelStyle: TextStyle(color: Colors.white), // Label color
      // enabledBorder: OutlineInputBorder(
      //   borderSide: BorderSide(
      //     color: Color.fromRGBO(255, 215, 0, 1.0), // Gold color when not focused
      //     width: 1.5, // Regular border width
      //   ),
      // ),
      focusedBorder: OutlineInputBorder(
        borderSide: BorderSide(
          color: Color.fromRGBO(255, 215, 0, 1.0), // Gold color when focused
          width: 2.5, // Thicker border when focused (more prominent)
        ),
      ),
      // border: OutlineInputBorder(
      //   borderSide: BorderSide(
      //     color: Color.fromRGBO(255, 215, 0, 1.0), // Default border color
      //     width: 1.5, // Regular border width
      //   ),
      // ),
    ),
    style: TextStyle(color: Colors.white), // Input text color
    cursorColor: Color.fromRGBO(255, 215, 0, 1.0), // Gold color cursor
    keyboardType: keyboardType,
  );
}


}










//Basic widgets:

// Character Sheet
// 1. Basic Information
// Name:
// Class/Profession:
// Race/Species:
// Background/Origin:
// Age:
// Gender:
// Alignment:
// Player Name:
// 2. Attributes/Abilities
// Strength (STR):
// Dexterity (DEX):
// Constitution (CON):
// Intelligence (INT):
// Wisdom (WIS):
// Charisma (CHA):
// 3. Skills
// Skill 1: [Skill Level/Bonus]
// Skill 2: [Skill Level/Bonus]
// Skill 3: [Skill Level/Bonus]
// (Include any additional skills relevant to the game)
// 4. Combat Stats
// Hit Points (HP):
// Armor Class (AC):
// Initiative Bonus:
// Attack Bonus (Melee/Ranged):
// Damage (Melee/Ranged):
// Special Abilities:
// 5. Equipment
// Weapons:
// Armor:
// Gear/Items:
// Magic Items (if applicable):
// 6. Spells/Powers (if applicable)
// Spell/Powers List:
// Name:
// Description:
// Usage/Charges:
// 7. Background & Personal Details
// Backstory:
// Personality Traits:
// Goals/Motivations:
// Allies/Contacts:
// Enemies/Rivals:
// 8. Notes & Miscellaneous
// Current Quests/Adventures:
// Important Locations:
// Events/Significant Moments:
// Miscellaneous Notes: