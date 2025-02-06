import 'package:flutter/material.dart';


class GameHomePage extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Game Home Page'),
      ),
      body: Center(
        child: Text('Welcome to the Game Home Page'),
      ),
    );
  }
}