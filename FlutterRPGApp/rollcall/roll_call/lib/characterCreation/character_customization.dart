

// TODO Make image bigger for display
// TODO Have select "name for selection"
// TODO When you click clear have it deselct options
// TODO set up layout better and make it reusable

import 'package:flutter/material.dart';
import 'package:multi_select_flutter/multi_select_flutter.dart';
import 'dropdownselection.dart';
import 'package:firebase_auth/firebase_auth.dart';
import 'package:cloud_firestore/cloud_firestore.dart';
import 'character_layout.dart';
import 'charactercustomizationhelper.dart';


class CharacterCustomizationScreen extends StatefulWidget {
   final String gameID;

  const CharacterCustomizationScreen({required this.gameID, Key? key}) : super(key: key);

  @override
  _CharacterCustomizationScreenState createState() => _CharacterCustomizationScreenState();
}

class _CharacterCustomizationScreenState extends State<CharacterCustomizationScreen> {
  final CharacterCustomization character = CharacterCustomization();
  // final String gameID;
  //   _CharacterCustomizationScreenState({required this.gameID});

  @override
  Widget build(BuildContext context) {
    final String gameID = widget.gameID;

    return Scaffold(
      
      appBar: AppBar(
        title: Text('Character Customization'),
      ),
       
       body: Container(
    width: MediaQuery.of(context).size.width,
    height: MediaQuery.of(context).size.height,
    decoration: BoxDecoration(
      image: DecorationImage(
        image: AssetImage('lib/assets/images/backgrounds/darkgreen.png'), // Path to your image
        fit: BoxFit.cover, // Ensures the image covers the entire screen
      ),
    ),
       
       child: SingleChildScrollView(
      child: Row(
        children: [
          // Left side with dropdowns
          Expanded(
            flex: 1,
            child: SingleChildScrollView(
              child: Column(
                children: [
                   buildMultiSelectDropdown('Base', baseOptions, (selectedValues) {
                    setState(() {
                      character.bases = selectedValues;
                    });
                  }),
                  buildMultiSelectDropdown('Head', headOptions, (selectedValues) {
                    setState(() {
                      character.heads = selectedValues;
                    });
                  }),
                  buildMultiSelectDropdown('Hair', hairOptions, (selectedValues) {
                    setState(() {
                      character.hairs = selectedValues;
                    });
                  }),
                  buildMultiSelectDropdown('Accessories', accessoriesOptions, (selectedValues) {
                    setState(() {
                      character.accessories = selectedValues;
                    });
                  }),
                  buildMultiSelectDropdown('Ear', earOptions, (selectedValues) {
                    setState(() {
                      character.ears = selectedValues;
                    });
                  }),
                  buildMultiSelectDropdown('Eyebrows', eyebrowsOptions, (selectedValues) {
                    setState(() {
                      character.eyebrows = selectedValues;
                    });
                  }),
                ],
              ),
            ),
          ),

          // Character customization area
         Expanded(
  flex: 2,
  child: Column(
    children: [
      Container(
        height: 374,
        width: 262,
        color: character.backgroundColor,
        child: Stack(
          children: [
            // Base
            ...character.bases.map((fileName) {
              return FutureBuilder<Image>(
                future: loadPng(fileName),
                builder: (context, snapshot) {
                  if (snapshot.hasData) {
                    // return Positioned.fill(child: snapshot.data!);
                   return Positioned.fill(
                    child: Image(
                      image: snapshot.data!.image,
                      fit: BoxFit.fill, // Ensure the image fills the entire space
                    ),
                  );
                  } else if (snapshot.hasError) {
                    return Center(child: Text('Error loading image'));
                  } else {
                    return const Center(child: CircularProgressIndicator());
                  }
                },
              );
            }).toList(),
            
            // Pants
            ...character.pants.map((fileName) {
              return FutureBuilder<Image>(
                future: loadPng(fileName),
                builder: (context, snapshot) {
                  if (snapshot.hasData) {
   return Positioned.fill(
                    child: Image(
                      image: snapshot.data!.image,
                      fit: BoxFit.fill, // Ensure the image fills the entire space
                    ),
                  );                  } else if (snapshot.hasError) {
                    return Center(child: Text('Error loading image'));
                  } else {
                    return const Center(child: CircularProgressIndicator());
                  }
                },
              );
            }).toList(),
            
            // Shirts
            ...character.shirts.map((fileName) {
              return FutureBuilder<Image>(
                future: loadPng(fileName),
                builder: (context, snapshot) {
                  if (snapshot.hasData) {
   return Positioned.fill(
                    child: Image(
                      image: snapshot.data!.image,
                      fit: BoxFit.fill, // Ensure the image fills the entire space
                    ),
                  );                  } else if (snapshot.hasError) {
                    return Center(child: Text('Error loading image'));
                  } else {
                    return const Center(child: CircularProgressIndicator());
                  }
                },
              );
            }).toList(),
            
            // Eyes
            ...character.eyes.map((fileName) {
              return FutureBuilder<Image>(
                future: loadPng(fileName),
                builder: (context, snapshot) {
                  if (snapshot.hasData) {
   return Positioned.fill(
                    child: Image(
                      image: snapshot.data!.image,
                      fit: BoxFit.fill, // Ensure the image fills the entire space
                    ),
                  );                  } else if (snapshot.hasError) {
                    return Center(child: Text('Error loading image'));
                  } else {
                    return const Center(child: CircularProgressIndicator());
                  }
                },
              );
            }).toList(),
            
            // Accessories
            ...character.accessories.map((fileName) {
              return FutureBuilder<Image>(
                future: loadPng(fileName),
                builder: (context, snapshot) {
                  if (snapshot.hasData) {
   return Positioned.fill(
                    child: Image(
                      image: snapshot.data!.image,
                      fit: BoxFit.fill, // Ensure the image fills the entire space
                    ),
                  );                  } else if (snapshot.hasError) {
                    return Center(child: Text('Error loading image'));
                  } else {
                    return const Center(child: CircularProgressIndicator());
                  }
                },
              );
            }).toList(),
            
            // Equipments
            ...character.equipment.map((fileName) {
              return FutureBuilder<Image>(
                future: loadPng(fileName),
                builder: (context, snapshot) {
                  if (snapshot.hasData) {
   return Positioned.fill(
                    child: Image(
                      image: snapshot.data!.image,
                      fit: BoxFit.fill, // Ensure the image fills the entire space
                    ),
                  );                  } else if (snapshot.hasError) {
                    return Center(child: Text('Error loading image'));
                  } else {
                    return const Center(child: CircularProgressIndicator());
                  }
                },
              );
            }).toList(),
            
            // Face
            ...character.face.map((fileName) {
              return FutureBuilder<Image>(
                future: loadPng(fileName),
                builder: (context, snapshot) {
                  if (snapshot.hasData) {
   return Positioned.fill(
                    child: Image(
                      image: snapshot.data!.image,
                      fit: BoxFit.fill, // Ensure the image fills the entire space
                    ),
                  );                  } else if (snapshot.hasError) {
                    return Center(child: Text('Error loading image'));
                  } else {
                    return const Center(child: CircularProgressIndicator());
                  }
                },
              );
            }).toList(),
            
            // Eyebrows
            ...character.eyebrows.map((fileName) {
              return FutureBuilder<Image>(
                future: loadPng(fileName),
                builder: (context, snapshot) {
                  if (snapshot.hasData) {
   return Positioned.fill(
                    child: Image(
                      image: snapshot.data!.image,
                      fit: BoxFit.fill, // Ensure the image fills the entire space
                    ),
                  );                  } else if (snapshot.hasError) {
                    return Center(child: Text('Error loading image'));
                  } else {
                    return const Center(child: CircularProgressIndicator());
                  }
                },
              );
            }).toList(),
            
            // Hairs
            ...character.hairs.map((fileName) {
              return FutureBuilder<Image>(
                future: loadPng(fileName),
                builder: (context, snapshot) {
                  if (snapshot.hasData) {
   return Positioned.fill(
                    child: Image(
                      image: snapshot.data!.image,
                      fit: BoxFit.fill, // Ensure the image fills the entire space
                    ),
                  );                  } else if (snapshot.hasError) {
                    return Center(child: Text('Error loading image'));
                  } else {
                    return const Center(child: CircularProgressIndicator());
                  }
                },
              );
            }).toList(),
            
            // Heads
            ...character.heads.map((fileName) {
              return FutureBuilder<Image>(
                future: loadPng(fileName),
                builder: (context, snapshot) {
                  if (snapshot.hasData) {
   return Positioned.fill(
                    child: Image(
                      image: snapshot.data!.image,
                      fit: BoxFit.fill, // Ensure the image fills the entire space
                    ),
                  );                  } else if (snapshot.hasError) {
                    return Center(child: Text('Error loading image'));
                  } else {
                    return const Center(child: CircularProgressIndicator());
                  }
                },
              );
            }).toList(),
            
            // Ears
            ...character.ears.map((fileName) {
              return FutureBuilder<Image>(
                future: loadPng(fileName),
                builder: (context, snapshot) {
                  if (snapshot.hasData) {
 return Positioned.fill(
                    child: Image(
                      image: snapshot.data!.image,
                      fit: BoxFit.fill, // Ensure the image fills the entire space
                    ),
                  );                  } else if (snapshot.hasError) {
                    return Center(child: Text('Error loading image'));
                  } else {
                    return const Center(child: CircularProgressIndicator());
                  }
                },
              );
              }).toList(),
          ],
        ),
      ),
    

ElevatedButton(
                    onPressed: () async {
                      try {
                        final user = FirebaseAuth.instance.currentUser;

                        if (user == null) {
                          throw Exception("User is not logged in.");
                        }

                        // Save the character's selected images
                        final gameDoc = FirebaseFirestore.instance
                            .collection('users')
                            .doc(user.uid)
                            .collection('games')
                            .doc(gameID);

                        await gameDoc.set({
                          'characterimage': FieldValue.arrayUnion(character.getSelectedImages()),
                        }, SetOptions(merge: true));

                        print("Character images saved successfully!");

                        // Navigate to CharacterSheetForm, passing gameID
                        Navigator.push(
                          context,
                          MaterialPageRoute(
                            builder: (context) => CharacterSheetForm(gameID: gameID),
                          ),
                        );
                      } catch (e) {
                        print("Error saving character images: $e");
                        ScaffoldMessenger.of(context).showSnackBar(
                          SnackBar(content: Text("Error saving character images: $e")),
                        );
                      }
                    },

                     style: ElevatedButton.styleFrom(
    backgroundColor: const Color.fromARGB(255, 246, 211, 115), // Background color
    foregroundColor: Colors.black, // Text color
    padding: EdgeInsets.symmetric(horizontal: 20, vertical: 10), // Optional: padding
  ),
                    child: Text('Save & Navigate'),
                  ),


           ],
            ),
          ),

          // Right side with dropdowns
          Expanded(
            flex: 1,
            child: SingleChildScrollView(
              child: Column(
                children: [
                  buildMultiSelectDropdown('Face', faceOptions, (selectedValues) {
                    setState(() {
                      character.face = selectedValues;
                    });
                  }),
                  buildMultiSelectDropdown('Eyes', eyesOptions, (selectedValues) {
                    setState(() {
                      character.eyes = selectedValues;
                    });
                  }),
                  buildMultiSelectDropdown('Equipment', equipmentOptions, (selectedValues) {
                    setState(() {
                      character.equipment = selectedValues;
                    });
                  }),
                  buildMultiSelectDropdown('Pants', pantsOptions, (selectedValues) {
                    setState(() {
                      character.pants = selectedValues;
                    });
                  }),
                  buildMultiSelectDropdown('Shirts', shirtsOptions, (selectedValues) {
                    setState(() {
                      character.shirts = selectedValues;
                    });
                  }),
                  buildMultiSelectDropdown('Background Color', colorOptions, (selectedValues) {
                    if (selectedValues.isNotEmpty) {
                      setState(() {
                        character.backgroundColor = _colorFromName(selectedValues.first);
                      });
                    }
                  }),
                ],
              ),
            ),
          ),
        ],
      ),
       )
    ) );
    
  }

  Widget buildMultiSelectDropdown(
      String category, Map<String, String> options, void Function(List<String>) onChanged) {
          String firstOption = options.isNotEmpty ? options.values.first : 'Test';


    return MultiSelectDialogField<String>(
      
title: Text(
      "Select $category", // Dynamic title text
      // style: const TextStyle(
        // fontSize: 2,
        //  fontWeight: FontWeight.bold),
    ),      
      items: convertOptions(options),
      initialValue: character.getValuesForCategory(category),
      onConfirm: (values) {
        onChanged(values);
      },
      searchable: true,
      decoration: BoxDecoration(
        border: Border.all(color: const Color.fromARGB(255, 246, 211, 115)),
        borderRadius: BorderRadius.circular(8),

      ),
    

buttonText: Text(
    firstOption,
      style: TextStyle(
        color: Colors.white,
        fontSize: 10,
        fontWeight: FontWeight.bold,
      ),
    ),


      chipDisplay: MultiSelectChipDisplay(
        
       chipColor: const Color.fromARGB(255, 246, 211, 115), // Background color of selected chips
      textStyle: TextStyle(color: const Color.fromARGB(255, 13, 13, 13), fontWeight: FontWeight.bold),
        onTap: (value) {
          setState(() {
            character.removeFromCategory(category, value);
          });
        },
      ),
      
      
    );
  }
 List<MultiSelectItem<String>> convertOptions(Map<String, String> options) {
    return options.entries
        .map((entry) => MultiSelectItem(entry.value, entry.key))
        .toList();
  }







  Color _colorFromName(String colorName) {
    switch (colorName) {
      //Do a color select wheel maybe? 
      case 'Pink': return const Color.fromARGB(255, 233, 204, 214);
      case 'Blue': return Colors.blue;
      case 'Black': return Colors.black;
      case 'White': return Colors.white;
      case 'Green': return Colors.green;
      case 'Red': return Colors.red;
      default: return Colors.white;
    }
  }
 
}


