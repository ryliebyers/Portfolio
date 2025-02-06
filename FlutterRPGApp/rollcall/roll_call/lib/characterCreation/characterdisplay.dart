import 'dart:io';

import 'package:flutter/material.dart';
import 'package:firebase_auth/firebase_auth.dart';
import 'package:cloud_firestore/cloud_firestore.dart';
import 'package:roll_call/game_selection.dart';
import 'package:roll_call/dice.dart';

class CharacterDisplayScreen extends StatefulWidget {
  final String userId;
  final String gameID;

  const CharacterDisplayScreen({Key? key, required this.userId, required this.gameID})
      : super(key: key);

  @override
  _CharacterDisplayScreenState createState() => _CharacterDisplayScreenState();
}

class _CharacterDisplayScreenState extends State<CharacterDisplayScreen> {
  Map<String, dynamic>? characterData;
List<String>? characterImage;

  bool isLoading = true;






  @override
  void initState() {
    super.initState();
    _fetchCharacterData();
  }

  Future<void> _fetchCharacterData() async {
    try {
      final doc = await FirebaseFirestore.instance
          .collection("users")
          .doc(widget.userId)
          .collection("games")
          .doc(widget.gameID)
          .get();

      if (doc.exists) {
        setState(() {
          characterData = doc.data()?['characterData'];
          characterImage = List<String>.from(doc.data()?['characterimage'] ?? []);

          isLoading = false;
        });
      } else {
        setState(() {
          characterData = null;
          characterImage = null;

          isLoading = false;
        });
      }
    } catch (e) {
      print("Error fetching character data: $e");
      setState(() {
        characterData = null;
         characterImage = null;

        isLoading = false;
      });
    }
  }


Widget _buildCharacterImageSection() {
  if (characterImage == null || characterImage!.isEmpty) {
    return Text("No character image available.", style: TextStyle(color: Colors.white));
  }

  return SizedBox(
    width: 200, // Adjust width as needed
    height: 300, // Adjust height as needed
    child: Stack(
      children: characterImage!.asMap().entries.map((entry) {
        final index = entry.key;
        final imagePath = entry.value;

        // Assume the images are stored locally for this example
        return Positioned.fill(
          child: Image.asset(
            imagePath,
            fit: BoxFit.cover,
            key: ValueKey(index), // Helps Flutter track widgets efficiently
          ),
        );
      }).toList(),
    ),
  );
}

@override
Widget build(BuildContext context) {
  return Scaffold(
    appBar: AppBar(
      title: Text(
          'Character Display',
          style: TextStyle(color: Colors.white),
      ),
          backgroundColor: Colors.black,
      actions: [
        IconButton(
          icon: Icon(Icons.home,  color: Colors.white),
          onPressed: () {
            Navigator.pushAndRemoveUntil(
              context,
              MaterialPageRoute(builder: (context) => GameSelectionScreen()),
              (route) => false,
            );
          },
        ),
      ],
    ),
     body: Container(
      decoration: BoxDecoration(
        image: DecorationImage(
          image: AssetImage('lib/assets/images/backgrounds/darkgreen.png'), // Path to your image
          fit: BoxFit.cover, // Ensures the image covers the entire screen
        ),
      ),
    child: Stack(
      children: [
        isLoading
            ? Center(child: CircularProgressIndicator())
            : characterData == null
                ? Center(child: Text(
                          "No character data found.",
                          style: TextStyle(color: Colors.white),
                        ),
                      )
                : _buildCharacterDetails(), // Your scrollable content
        Positioned(
          bottom: 16, // Distance from the bottom
          right: 16,  // Distance from the right
          child: FloatingActionButton(
            backgroundColor: Colors.white,
                foregroundColor: Colors.amber,
            onPressed: () {
              // Show the pop-up (dialog) instead of navigating to another screen
              showDialog(
                context: context,
                builder: (BuildContext context) {
                  return AlertDialog(
                   backgroundColor: Colors.white,
                    title: Text(
                          'Dice Roller',
                          style: TextStyle(color: Colors.white),
                        ),

                    content: DiceRoller(), // Your Dice Roller widget in the dialog
                    actions: <Widget>[
                      TextButton(
                        child: Text('Close'),
                        onPressed: () {
                          Navigator.of(context).pop(); // Close the dialog
                        },
                      ),
                    ],
                  );
                },
              );
            },
            child: Icon(Icons.casino), // Dice icon
          ),
        ),
      ],
    ),
     ),
  );
}




  Widget _buildCharacterDetails() {
    return SingleChildScrollView(
      padding: EdgeInsets.all(16.0),
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
        _buildSection("Character Image", _buildCharacterImageSection()),

          _buildSection("Basic Information", _buildBasicInfoSection()),
          _buildSection("Attributes/Abilities", _buildAttributesSection()),
          _buildSection("Skills", _buildSkillsSection()),
          _buildSection("Combat Stats", _buildCombatStatsSection()),
          _buildSection("Equipment", _buildEquipmentSection()),
          _buildSection("Spells/Powers", _buildSpellsSection()),
          _buildSection("Background & Personal Details", _buildBackgroundDetailsSection()),
          _buildSection("Notes & Miscellaneous", _buildNotesSection()),
        ],
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
        Divider(thickness: 2,  color: Colors.amber),
      ],
    );
  }

 

  Widget _buildBasicInfoSection() {
  final basicInfo = characterData?['basicInfo'] ?? {};
  return Column(
    crossAxisAlignment: CrossAxisAlignment.start,
    children: basicInfo.entries.map<Widget>((entry) {
      return Text("${entry.key}: ${entry.value}", style: TextStyle(color: Colors.white));
    }).toList(),
  );
}


Widget _buildAttributesSection() {
  final attributes = characterData?['attributes'] ?? {};
  return Column(
    crossAxisAlignment: CrossAxisAlignment.start,
    children: attributes.entries.map<Widget>((entry) {
      return Text("${entry.key}: ${entry.value}", style: TextStyle(color: Colors.white));
    }).toList(),
  );
}


  Widget _buildSkillsSection() {
    final skills = characterData?['skills'] ?? [];
    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: skills.map<Widget>((skill) {
        return Text("Skill: ${skill['Skill Name']}, Level/Bonus: ${skill['Level/Bonus']}", style: TextStyle(color: Colors.white));
      }).toList(),
    );
  }

Widget _buildCombatStatsSection() {
  final combatStats = characterData?['combatStats'] ?? {};
  return Column(
    crossAxisAlignment: CrossAxisAlignment.start,
    children: combatStats.entries.map<Widget>((entry) {
      return Text("${entry.key}: ${entry.value}", style: TextStyle(color: Colors.white));
    }).toList(),
  );
}

  Widget _buildEquipmentSection() {
    final equipment = characterData?['equipment'] ?? {};
    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        _buildListSection("Weapons", equipment['weapons']),
        _buildListSection("Armor", equipment['armor']),
        _buildListSection("Gear/Items", equipment['gear']),
        _buildListSection("Magic Items", equipment['magicItems']),
      ],
    );
  }

  Widget _buildListSection(String title, List<dynamic>? items) {
    if (items == null || items.isEmpty) return Text("$title: None",style: TextStyle(color: Colors.white));
    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Text("$title:", style: TextStyle(color: Colors.white)),
        ...items.map((item) => Text("- $item", style: TextStyle(color: Colors.white))).toList(),
      ],
    );
  }

  Widget _buildSpellsSection() {
    final spells = characterData?['spells'] ?? [];
    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: spells.map<Widget>((spell) {
        return Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Text("Spell: ${spell['Spell Name']}", style: TextStyle(color: Colors.white)),
            Text("Description: ${spell['Description']}", style: TextStyle(color: Colors.white)),
            Text("Usage: ${spell['Usage']}", style: TextStyle(color: Colors.white)),
          ],
        );
      }).toList(),
    );
  }

 Widget _buildBackgroundDetailsSection() {
  final backgroundDetails = characterData?['backgroundDetails'] ?? {};
  return Column(
    crossAxisAlignment: CrossAxisAlignment.start,
    children: backgroundDetails.entries.map<Widget>((entry) {
      return Text("${entry.key}: ${entry.value}", style: TextStyle(color: Colors.white));
    }).toList(),
  );
}


  Widget _buildNotesSection() {
    final notes = characterData?['notes'] ?? {};
    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        _buildListSection("Quests", notes['quests']),
        _buildListSection("Locations", notes['locations']),
        _buildListSection("Events", notes['events']),
        Text("Miscellaneous: ${notes['miscellaneous']}", style: TextStyle(color: Colors.white)),
      ],
    );
  }
}


// add inventory, health, and make things customizable


