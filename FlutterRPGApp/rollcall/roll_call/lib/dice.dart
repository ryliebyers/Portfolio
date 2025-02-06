import 'package:flutter/material.dart';
// import 'package:flutter_cube/flutter_cube.dart';
import 'dart:math';



// void main() {
//   runApp(MyApp());
// }

// class MyApp extends StatelessWidget {
//   @override
//   Widget build(BuildContext context) {
//     return MaterialApp(
//       title: 'Dice Roller',
//       theme: ThemeData(
//         primarySwatch: Colors.blue,
//       ),
//       home: DiceRoller(),
//     );
//   }
// }

// class DiceRoller extends StatefulWidget {
//   @override
//   _DiceRollerState createState() => _DiceRollerState();
// }

// class _DiceRollerState extends State<DiceRoller> {
//   List<String> diceTypes = ['D20', 'D12', 'D10', 'D100', 'D8', 'D6', 'D4'];
//   List<String> selectedDice = [];
//   bool showDiceButtons = false;

//   void toggleDiceButtons() {
//     setState(() {
//       showDiceButtons = !showDiceButtons;
//     });
//   }

//   void rollDice() {
//     int total = 0;
//     for (String die in selectedDice) {
//       int sides = int.parse(die.substring(1));
//       total += Random().nextInt(sides) + 1;
//     }
//     showDialog(
//       context: context,
//       builder: (context) {
//         return AlertDialog(
//           title: Text('Total Roll'),
//           content: Text('You rolled a total of $total!'),
//           actions: [
//             TextButton(
//               onPressed: () => Navigator.of(context).pop(),
//               child: Text('OK'),
//             ),
//           ],
//         );
//       },
//     );
//   }

//   @override
//   Widget build(BuildContext context) {
//     return Scaffold(
//       appBar: AppBar(
//         title: Text('Dice Roller'),
//       ),
//       body: Center(
//         child: Column(
//           mainAxisAlignment: MainAxisAlignment.center,
//           children: [
//             ElevatedButton(
//               onPressed: toggleDiceButtons,
//               child: Text('Select Dice'),
//             ),
//             if (showDiceButtons) ...[
//               ...diceTypes.map((die) {
//                 return ElevatedButton(
//                   onPressed: () {
//                     setState(() {
//                       selectedDice.add(die);
//                     });
//                   },
//                   child: Text(die),
//                 );
//               }).toList(),
//               SizedBox(height: 20),
//               ElevatedButton(
//                 onPressed: rollDice,
//                 child: Text('Roll Dice'),
//               ),
//             ],
//             SizedBox(height: 20),
//             Text('Selected Dice: ${selectedDice.join(', ')}'),
//           ],
//         ),
//       ),
//     );
//   }
// }





void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Dice Roller',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: DiceRoller(),
    );
  }
}

class DiceRoller extends StatefulWidget {
  @override
  _DiceRollerState createState() => _DiceRollerState();
}

class _DiceRollerState extends State<DiceRoller> with SingleTickerProviderStateMixin {
  List<String> diceTypes = ['D20', 'D12', 'D10', 'D100', 'D8', 'D6', 'D4'];
  List<String> selectedDice = [];
  bool showDiceButtons = false;
  // AnimationController? _controller;
  bool rolling = false;
  List<int> rolledResults = [];

  // @override
  // void initState() {
  //   super.initState();
  //   _controller = AnimationController(
  //     duration: const Duration(milliseconds: 1000),
  //     vsync: this,
  //   );
  // }

  // @override
  // void dispose() {
  //   _controller?.dispose();
  //   super.dispose();
  // }

  void toggleDiceButtons() {
    setState(() {
      showDiceButtons = !showDiceButtons;
    });
  }

  void rollDice() {
    if (selectedDice.isEmpty) return;

    setState(() {
      rolling = true;
      rolledResults = List.filled(selectedDice.length, 0); // Reset results for each die
    });

    // Start the animation and rolling effect
    // _controller?.repeat(reverse: true);

    Future.delayed(Duration(milliseconds: 1000), () {
      // _controller?.stop();
      List<int> results = [];
      int total = 0;

      for (String die in selectedDice) {
        int sides = int.parse(die.substring(1));
        int roll = Random().nextInt(sides) + 1;
        results.add(roll);
        total += roll;
      }

      setState(() {
        rolledResults = results; // Set the rolled results
        rolling = false; // End rolling
      });



// showDialog(
//   context: context,
//   builder: (context) {
//     return AlertDialog(
//       title: Text('Total Roll'),
//       content: SingleChildScrollView(
//         child: Column(
//           mainAxisSize: MainAxisSize.min,
//           children: [
//             Text('You rolled a total of $total!'),
//             SizedBox(height: 20),
//             for (int i = 0; i < selectedDice.length; i++) ...[
//               Column(
//                 children: [
//                   Text(selectedDice[i], style: TextStyle(fontSize: 18)),
//                   Stack(
//                     alignment: Alignment.center,
//                     children: [
//                       _getDiceOutline(selectedDice[i]),
//                       Text(
//                         rolledResults[i].toString(),
//                         style: TextStyle(
//                           fontSize: 24,
//                           color: Colors.red,
//                           fontWeight: FontWeight.bold,
//                           shadows: [
//                             Shadow(
//                               color: Colors.black,
//                               offset: Offset(1, 1),
//                               blurRadius: 3,
//                             ),
//                           ],
//                         ),
//                       ),
//                     ],
//                   ),
//                   SizedBox(height: 20),
//                 ],
//               ),
//             ],
//           ],
//         ),
//       ),
//       actions: [
//         TextButton(
//           onPressed: () => Navigator.of(context).pop(),
//           child: Text('OK'),
//         ),
//       ],
//     );
//   },
// );



showDialog(
  context: context,
  builder: (context) {
    return Dialog(
      child: SingleChildScrollView(
        child: Column(
          mainAxisSize: MainAxisSize.min,
          children: [
            Padding(
              padding: const EdgeInsets.all(16.0),
              child: Text(
                'Total Roll',
                style: TextStyle(fontSize: 20, fontWeight: FontWeight.bold),
              ),
            ),
            Divider(),
            Padding(
              padding: const EdgeInsets.symmetric(horizontal: 16.0),
              child: Column(
                children: [
                  Text('You rolled a total of $total!'),
                  SizedBox(height: 20),
                  for (int i = 0; i < selectedDice.length; i++) ...[
                    Column(
                      children: [
                        Text(
                          selectedDice[i],
                          style: TextStyle(fontSize: 18),
                        ),
                        Stack(
                          alignment: Alignment.center,
                          children: [
                            _getDiceOutline(selectedDice[i]),
                            Text(
                              rolledResults[i].toString(),
                              style: TextStyle(
                                fontSize: 24,
                                color: Colors.red,
                                fontWeight: FontWeight.bold,
                                shadows: [
                                  Shadow(
                                    color: Colors.black,
                                    offset: Offset(1, 1),
                                    blurRadius: 3,
                                  ),
                                ],
                              ),
                            ),
                          ],
                        ),
                        SizedBox(height: 20),
                      ],
                    ),
                  ],
                ],
              ),
            ),
            Divider(),
            TextButton(
              onPressed: () => Navigator.of(context).pop(),
              child: Text('OK'),
            ),
          ],
        ),
      ),
    );
  },
);



      // Show dialog with the total result
      // showDialog(
      //   context: context,
      //   builder: (context) {
      //     return AlertDialog(
      //       title: Text('Total Roll'),
      //       content: SingleChildScrollView(
      //         child: Column(
      //           mainAxisSize: MainAxisSize.min,
      //           children: [
      //             Text('You rolled a total of $total!'),
      //             SizedBox(height: 20),
      //             for (int i = 0; i < selectedDice.length; i++) ...[
      //               Column(
      //                 children: [
      //                   Text(selectedDice[i], style: TextStyle(fontSize: 18)),
      //                   Stack(
      //                     alignment: Alignment.center,
      //                     children: [
      //                       _getDiceOutline(selectedDice[i]),
      //                       Text(
      //                         rolledResults[i].toString(),
      //                         style: TextStyle(
      //                           fontSize: 24,
      //                           color: Colors.red,
      //                           fontWeight: FontWeight.bold,
      //                           shadows: [
      //                             Shadow(
      //                               color: Colors.black,
      //                               offset: Offset(1, 1),
      //                               blurRadius: 3,
      //                             ),
      //                           ],
      //                         ),
      //                       ),
      //                     ],
      //                   ),
      //                   SizedBox(height: 20),
      //                 ],
      //               ),
      //             ],
      //           ],
      //         ),
      //       ),
      //       actions: [
      //         TextButton(
      //           onPressed: () => Navigator.of(context).pop(),
      //           child: Text('OK'),
      //         ),
      //       ],
      //     );
      //   },
      // );
    });

    // Show random numbers during rolling
    // Future.delayed(Duration(milliseconds: 100), () {
    //   if (rolling) {
    //     setState(() {
    //       rolledResults = List.generate(selectedDice.length, (index) => Random().nextInt(20) + 1);
    //     });
    //   }
    // });
  }

  Widget _getDiceOutline(String die) {
    switch (die) {
      case 'D4':
        return CustomPaint(
          size: Size(50, 50),
          painter: DiceOutlinePainter(4),
        );
      case 'D6':
        return CustomPaint(
          size: Size(50, 50),
          painter: DiceOutlinePainter(6),
        );
      case 'D8':
        return CustomPaint(
          size: Size(50, 50),
          painter: DiceOutlinePainter(8),
        );
      case 'D10':
        return CustomPaint(
          size: Size(50, 50),
          painter: DiceOutlinePainter(10),
        );
      case 'D12':
        return CustomPaint(
          size: Size(50, 50),
          painter: DiceOutlinePainter(12),
        );
      case 'D20':
        return CustomPaint(
          size: Size(50, 50),
          painter: DiceOutlinePainter(20),
        );
      case 'D100':
        return CustomPaint(
          size: Size(50, 50),
          painter: DiceOutlinePainter(10), // Use D10 for representation
        );
      default:
        return Container();
    }
  }

  void clearSelection() {
    setState(() {
      selectedDice.clear();
      rolledResults.clear();
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Dice Roller'),
      ),
//       body: Center(
//         child: Column(
//           mainAxisAlignment: MainAxisAlignment.center,
//           children: [
//             ElevatedButton(
//               onPressed: toggleDiceButtons,
//               child: Text('Select Dice'),
//             ),
//             // if (showDiceButtons) ...[
//             //   ...diceTypes.map((die) {
//             //     return ElevatedButton(
//             //       onPressed: () {
//             //         setState(() {
//             //           selectedDice.add(die);
//             //         });
//             //       },
//             //       child: Text(die),
//             //     );
//             //   }).toList(),
//             //   SizedBox(height: 20),
//             //   ElevatedButton(
//             //     onPressed: rollDice,
//             //     child: Text('Roll Dice'),
//             //   ),
//             //   ElevatedButton(
//             //     onPressed: clearSelection,
//             //     child: Text('Clear Selection'),
//             //   ),
//             // ],

//            if (showDiceButtons) ...[
//   SizedBox(
//     height: 300, // Adjust the height to control the scrollable area
//     child: SingleChildScrollView(
//       child: Column(
//         children: [
//           for (String die in diceTypes)
//             ElevatedButton(
//               onPressed: () {
//                 setState(() {
//                   selectedDice.add(die);
//                 });
//               },
//               child: Text(die),
//             ),
//         ],
//       ),
//     ),
//   ),
//   SizedBox(height: 20),
//   ElevatedButton(
//     onPressed: rollDice,
//     child: Text('Roll Dice'),
//   ),
//   ElevatedButton(
//     onPressed: clearSelection,
//     child: Text('Clear Selection'),
//   ),
// ],


//             SizedBox(height: 20),
//             Text('Selected Dice: ${selectedDice.join(', ')}'),
//           ],
//         ),
//       ),





body: Center(
  child: Column(
    mainAxisAlignment: MainAxisAlignment.center,
    children: [
      ElevatedButton(
        onPressed: toggleDiceButtons,
        child: Text('Select Dice'),
      ),
      if (showDiceButtons) ...[
        Flexible(
          child: SizedBox(
            height: 300, // Adjust the height as needed
            child: SingleChildScrollView(
              child: Column(
                children: [
                  for (String die in diceTypes)
                    ElevatedButton(
                      onPressed: () {
                        setState(() {
                          selectedDice.add(die);
                        });
                      },
                      child: Text(die),
                    ),
                ],
              ),
            ),
          ),
        ),
        SizedBox(height: 20),
        ElevatedButton(
          onPressed: selectedDice.isEmpty
              ? null // Disable button if no dice are selected
              : rollDice,
          child: Text('Roll Dice'),
        ),
        ElevatedButton(
          onPressed: selectedDice.isEmpty
              ? null // Disable button if no dice are selected
              : clearSelection,
          child: Text('Clear Selection'),
        ),
      ],
      SizedBox(height: 20),
      Text(
        selectedDice.isNotEmpty
            ? 'Selected Dice: ${selectedDice.join(', ')}'
            : 'No dice selected',
        style: TextStyle(fontSize: 16),
      ),
    ],
  ),
),






    );
  }
}

class DiceOutlinePainter extends CustomPainter {
  final int sides;

  DiceOutlinePainter(this.sides);

  @override
  void paint(Canvas canvas, Size size) {
    Paint paintOutline = Paint()
      ..color = Colors.black
      ..style = PaintingStyle.stroke
      ..strokeWidth = 2;

    Paint paintFill = Paint()
      ..shader = RadialGradient(
        colors: [Color(0xFFFFD700), Color(0xFFD1A30E)],
        stops: [0.4, 1.0],
      ).createShader(Rect.fromCircle(center: Offset(size.width / 2, size.height / 2), radius: size.width / 2));

    // Draw the dice shape
    switch (sides) {
      case 4:
        _drawD4(canvas, size, paintOutline, paintFill);
        break;
      case 6:
        _drawD6(canvas, size, paintOutline, paintFill);
        break;
      case 8:
        _drawD8(canvas, size, paintOutline, paintFill);
        break;
      case 10:
        _drawD10(canvas, size, paintOutline, paintFill);
        break;
      case 12:
        _drawD12(canvas, size, paintOutline, paintFill);
        break;
      case 20:
        _drawD20(canvas, size, paintOutline, paintFill);
        break;
      case 100:
        // Treat D100 as two D10s shown side by side.
        canvas.save();
        _drawD10(canvas, size, paintOutline, paintFill);
        canvas.translate(size.width * 1.2, 0); // Move for the second D10
        _drawD10(canvas, size, paintOutline, paintFill);
        canvas.restore();
        break;
    }
  }

  void _drawD4(Canvas canvas, Size size, Paint outline, Paint fill) {
    Path path = Path()
      ..moveTo(size.width / 2, 0)
      ..lineTo(size.width, size.height)
      ..lineTo(0, size.height)
      ..close();
    canvas.drawPath(path, fill);
    canvas.drawPath(path, outline);
    canvas.drawShadow(path, Colors.black.withOpacity(0.5), 4, true);
  }

  void _drawD6(Canvas canvas, Size size, Paint outline, Paint fill) {
    Rect rect = Rect.fromLTWH(0, 0, size.width, size.height);
    Path path = Path()..addRect(rect);
    canvas.drawPath(path, fill);
    canvas.drawPath(path, outline);
    canvas.drawShadow(path, Colors.black.withOpacity(0.5), 4, true);
  }

  void _drawD8(Canvas canvas, Size size, Paint outline, Paint fill) {
    Path path = Path();
    path.moveTo(size.width / 2, 0);
    path.lineTo(size.width, size.height / 4);
    path.lineTo(size.width, size.height * 3 / 4);
    path.lineTo(size.width / 2, size.height);
    path.lineTo(0, size.height * 3 / 4);
    path.lineTo(0, size.height / 4);
    path.close();
    canvas.drawPath(path, fill);
    canvas.drawPath(path, outline);
    canvas.drawShadow(path, Colors.black.withOpacity(0.5), 4, true);
  }

  void _drawD10(Canvas canvas, Size size, Paint outline, Paint fill) {
    Path path = Path();
    double radius = size.width / 2;
    for (int i = 0; i < 10; i++) {
      double angle = (2 * pi / 10) * i;
      double x = radius + radius * cos(angle);
      double y = radius + radius * sin(angle);
      if (i == 0) {
        path.moveTo(x, y);
      } else {
        path.lineTo(x, y);
      }
    }
    path.close();
    canvas.drawPath(path, fill);
    canvas.drawPath(path, outline);
    canvas.drawShadow(path, Colors.black.withOpacity(0.5), 4, true);
  }

  void _drawD12(Canvas canvas, Size size, Paint outline, Paint fill) {
    Path path = Path();
    double radius = size.width / 2;
    for (int i = 0; i < 12; i++) {
      double angle = (2 * pi / 12) * i;
      double x = radius + radius * cos(angle);
      double y = radius + radius * sin(angle);
      if (i == 0) {
        path.moveTo(x, y);
      } else {
        path.lineTo(x, y);
      }
    }
    path.close();
    canvas.drawPath(path, fill);
    canvas.drawPath(path, outline);
    canvas.drawShadow(path, Colors.black.withOpacity(0.5), 4, true);
  }

  void _drawD20(Canvas canvas, Size size, Paint outline, Paint fill) {
    Path path = Path();
    double radius = size.width / 2;
    for (int i = 0; i < 20; i++) {
      double angle = (2 * pi / 20) * i;
      double x = radius + radius * cos(angle);
      double y = radius + radius * sin(angle);
      if (i == 0) {
        path.moveTo(x, y);
      } else {
        path.lineTo(x, y);
      }
    }
    path.close();
    canvas.drawPath(path, fill);
    canvas.drawPath(path, outline);
    canvas.drawShadow(path, Colors.black.withOpacity(0.5), 4, true);
  }

  @override
  bool shouldRepaint(covariant CustomPainter oldDelegate) {
    return true;
  }
}

