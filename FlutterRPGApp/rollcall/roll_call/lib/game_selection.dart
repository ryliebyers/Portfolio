import 'package:flutter/gestures.dart';
import 'package:flutter/material.dart';
import 'characterCreation/character_customization.dart';
import 'authentificationScreens/signin.dart';
import 'package:firebase_auth/firebase_auth.dart';
import 'package:uuid/uuid.dart';
import 'package:cloud_firestore/cloud_firestore.dart';
import 'characterCreation/characterdisplay.dart';






class GameSelectionScreen extends StatefulWidget {
  @override
  _GameSelectionScreenState createState() => _GameSelectionScreenState();
}

class _GameSelectionScreenState extends State<GameSelectionScreen> {
  late Future<bool> game1Status;
  late Future<bool> game2Status;
  late Future<bool> game3Status;

  @override
  void initState() {
    super.initState();
    String userId = FirebaseAuth.instance.currentUser!.uid;
    game1Status = isPathEmpty(userId, 'game1');
    game2Status = isPathEmpty(userId, 'game2');
    game3Status = isPathEmpty(userId, 'game3');
  }

  Future<void> deleteGame(String userId, String gameId) async {
    try {
      await FirebaseFirestore.instance
          .collection('users')
          .doc(userId)
          .collection('games')
          .doc(gameId)
          .delete();
      setState(() {
        if (gameId == 'game1') game1Status = Future.value(true);
        if (gameId == 'game2') game2Status = Future.value(true);
        if (gameId == 'game3') game3Status = Future.value(true);
      });
      ScaffoldMessenger.of(context).showSnackBar(
        SnackBar(content: Text('Game $gameId deleted successfully.')),
      );
    } catch (e) {
      print('Error deleting game: $e');
      ScaffoldMessenger.of(context).showSnackBar(
        SnackBar(content: Text('Failed to delete game $gameId.')),
      );
    }
  }


  Future<void> deleteAccount(BuildContext context) async {
    String userId = FirebaseAuth.instance.currentUser!.uid;
    try {
      // Delete user data from Firestore
      await FirebaseFirestore.instance.collection('users').doc(userId).delete();

      // Delete user authentication account
      await FirebaseAuth.instance.currentUser!.delete();

      // Navigate to SignInPage
      Navigator.pushReplacement(
        context,
        MaterialPageRoute(builder: (context) => SignInPage()),
      );

      ScaffoldMessenger.of(context).showSnackBar(
        SnackBar(content: Text('Account deleted successfully.')),
      );
    } catch (e) {
      print('Error deleting account: $e');
      ScaffoldMessenger.of(context).showSnackBar(
        SnackBar(content: Text('Failed to delete account. Please try again.')),
      );
    }
  }


  // @override
  // Widget build(BuildContext context) {
  //   String userId = FirebaseAuth.instance.currentUser!.uid;

  //   return Scaffold(
  //     appBar: AppBar(
  //       title: Text('Select a Game'),
  //       actions: [
  //         IconButton(
  //           icon: Icon(Icons.logout),
  //           onPressed: () {
  //             FirebaseAuth.instance.signOut().then((value) {
  //               print("Signed Out");
  //               Navigator.pushReplacement(
  //                 context,
  //                 MaterialPageRoute(builder: (context) => SignInPage()),
  //               );
  //             });
  //           },
  //         ),
  //       ],
  //     ),
  //     body: Container(
  //       decoration: BoxDecoration(
  //         image: DecorationImage(
  //           image: AssetImage('lib/assets/images/backgrounds/darkgreen.png'),
  //           fit: BoxFit.cover,
  //         ),
  //       ),
  //       child: Center(
  //         child: Column(
  //           mainAxisAlignment: MainAxisAlignment.center,
  //           children: <Widget>[
  //             buildGameRow(context, userId, 'game1', game1Status),
  //             SizedBox(height: 20),
  //             buildGameRow(context, userId, 'game2', game2Status),
  //             SizedBox(height: 20),
  //             buildGameRow(context, userId, 'game3', game3Status),
  //           ],
  //         ),
  //       ),
  //     ),
  //   );
  // }

    @override
  Widget build(BuildContext context) {
    String userId = FirebaseAuth.instance.currentUser!.uid;

    return Scaffold(
      appBar: AppBar(
        title: Text('Select a Game'),
        actions: [
          IconButton(
            icon: Icon(Icons.account_circle),
            onPressed: () {
              showModalBottomSheet(
                context: context,
                builder: (context) => Column(
                  mainAxisSize: MainAxisSize.min,
                  children: [
                    ListTile(
                      leading: Icon(Icons.person),
                      title: Text('View Account'),
                      onTap: () {
                        Navigator.pop(context);
                        ScaffoldMessenger.of(context).showSnackBar(
                          SnackBar(content: Text('Account: $userId')),
                        );
                      },
                    ),
                    ListTile(
                      leading: Icon(Icons.delete, color: Colors.red),
                      title: Text('Delete Account'),
                      onTap: () {
                        Navigator.pop(context);
                        showDialog(
                          context: context,
                          builder: (context) => AlertDialog(
                            title: Text('Delete Account'),
                            content: Text(
                                'Are you sure you want to delete your account? This action cannot be undone.'),
                            actions: [
                              TextButton(
                                onPressed: () => Navigator.pop(context),
                                child: Text('Cancel'),
                              ),
                              TextButton(
                                onPressed: () {
                                  Navigator.pop(context);
                                  deleteAccount(context);
                                },
                                child: Text('Delete', style: TextStyle(color: Colors.red)),
                              ),
                            ],
                          ),
                        );
                      },
                    ),
                  ],
                ),
              );
            },
          ),
          IconButton(
            icon: Icon(Icons.logout),
            onPressed: () {
              FirebaseAuth.instance.signOut().then((value) {
                print("Signed Out");
                Navigator.pushReplacement(
                  context,
                  MaterialPageRoute(builder: (context) => SignInPage()),
                );
              });
            },
          ),
        ],
      ),
      body: Container(
        decoration: BoxDecoration(
          image: DecorationImage(
            image: AssetImage('lib/assets/images/backgrounds/darkgreen.png'),
            fit: BoxFit.cover,
          ),
        ),
        child: Center(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: <Widget>[
              buildGameRow(context, userId, 'game1', game1Status),
              SizedBox(height: 20),
              buildGameRow(context, userId, 'game2', game2Status),
              SizedBox(height: 20),
              buildGameRow(context, userId, 'game3', game3Status),
            ],
          ),
        ),
      ),
    );
  }

  Widget buildGameRow(
      BuildContext context, String userId, String gameId, Future<bool> gameStatus) {
    return Row(
      mainAxisAlignment: MainAxisAlignment.center,
      children: [
        FutureBuilder<bool>(
          future: gameStatus,
          builder: (context, snapshot) {
            if (snapshot.connectionState == ConnectionState.waiting) {
              return CircularProgressIndicator();
            } else if (snapshot.hasError) {
              return Text('Error: ${snapshot.error}');
            } else {
              return ElevatedButton(
                onPressed: () {
                  if (snapshot.data!) {
                    // Path is empty, create new game
                    Navigator.push(
                      context,
                      MaterialPageRoute(
                        builder: (context) =>
                            CharacterCustomizationScreen(gameID: gameId),
                      ),
                    );
                  } else {
                    // Path is not empty, load saved game
                    Navigator.push(
                      context,
                      MaterialPageRoute(
                        builder: (context) =>
                            CharacterDisplayScreen(userId: userId, gameID: gameId),
                      ),
                    );
                  }
                },
                child: Text(
                  snapshot.data! ? '  New Game ' : 'Stored Game',
                  style: TextStyle(
                    color: Colors.green[800],
                    fontWeight: FontWeight.bold,
                  ),
                ),
              );
            }
          },
        ),
        SizedBox(width: 10),
        IconButton(
          icon: Icon(Icons.delete, color: Colors.red),
          onPressed: () {
            showDialog(
              context: context,
              builder: (context) => AlertDialog(
                title: Text('Delete Game'),
                content: Text('Are you sure you want to delete $gameId?'),
                actions: [
                  TextButton(
                    onPressed: () => Navigator.pop(context),
                    child: Text('No'),
                  ),
                  TextButton(
                    onPressed: () {
                      Navigator.pop(context);
                      deleteGame(userId, gameId);
                    },
                    child: Text('Yes'),
                  ),
                ],
              ),
            );
          },
        ),
      ],
    );
  }
}

Future<bool> isPathEmpty(String userId, String gameId) async {
  try {
    DocumentReference gameDocRef = FirebaseFirestore.instance
        .collection('users')
        .doc(userId)
        .collection('games')
        .doc(gameId);

    DocumentSnapshot gameSnapshot = await gameDocRef.get();

    if (!gameSnapshot.exists) return true;

    var characterData = gameSnapshot.get('characterData');
    var characterImage = gameSnapshot.get('characterimage');

    return characterData == null || characterImage == null || characterImage.isEmpty;
  } catch (e) {
    print('Error checking path: $e');
    return false;
  }
}











