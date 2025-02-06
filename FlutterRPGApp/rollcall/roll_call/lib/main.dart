
import 'package:flutter/material.dart';
import 'authentificationScreens/signin.dart';
import 'package:firebase_core/firebase_core.dart';
import 'firebase_options.dart';
import 'package:animated_splash_screen/animated_splash_screen.dart';







void main() async {
  WidgetsFlutterBinding.ensureInitialized();
   await Firebase.initializeApp(
    options: DefaultFirebaseOptions.currentPlatform
    );

  runApp( const MyApp());
}
 





class MyApp extends StatelessWidget {
const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: AnimatedSplashScreen(
        splash: 'lib/assets/images/backgrounds/splashScreen.gif',
        splashIconSize: 2000,
        centered: true,
        nextScreen: SignInPage(),
        backgroundColor: const Color.fromARGB(255, 1, 13, 1),
        duration: 3000,
      )
    );
  }
}