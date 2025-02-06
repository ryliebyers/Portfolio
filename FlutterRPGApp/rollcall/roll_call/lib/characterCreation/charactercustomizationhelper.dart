import 'package:flutter/material.dart';
import 'package:multi_select_flutter/multi_select_flutter.dart';
import 'dropdownselection.dart';
import 'package:firebase_auth/firebase_auth.dart';
import 'package:cloud_firestore/cloud_firestore.dart';
import 'character_layout.dart';


class CharacterCustomization {
  List<String> bases = [];
  List<String> heads = [];
  List<String> hairs = [];
  List<String> accessories = [];
  List<String> ears = [];
  List<String> eyebrows = [];
  List<String> eyes = [];
  List<String> equipment = [];
  List<String> face = [];
  List<String> pants = [];
  List<String> shirts = [];
  Color backgroundColor = Colors.white;

  Map<String, dynamic> toMap() {
    return {
      'bases': bases,
      'heads': heads,
      'hairs': hairs,
      'accessories': accessories,
      'ears': ears,
      'eyebrows': eyebrows,
      'eyes': eyes,
      'equipment': equipment,
      'face': face,
      'pants': pants,
      'shirts': shirts,
      'backgroundColor': '#${backgroundColor.value.toRadixString(16).padLeft(8, '0')}',
    };
  }

 List<String> getSelectedImages() {
    return [
      ...bases,
      ...heads,
      ...hairs,
      ...accessories,
      ...ears,
      ...eyebrows,
      ...face,
      ...eyes,
      ...equipment,
      ...pants,
      ...shirts,
    ];
  }




  List<String> getValuesForCategory(String category) {
    switch (category) {
      case 'Base': return bases;
      case 'Head': return heads;
      case 'Hair': return hairs;
      case 'Accessories': return accessories;
      case 'Ear': return ears;
      case 'Eyebrows': return eyebrows;
      case 'Eyes': return eyes;
      case 'Equipment': return equipment;
      case 'Face': return face;
      case 'Pants': return pants;
      case 'Shirts': return shirts;
      default: return [];
    }
  }

  void removeFromCategory(String category, String value) {
    switch (category) {
      case 'Base': bases.remove(value); break;
      case 'Head': heads.remove(value); break;
      case 'Hair': hairs.remove(value); break;
      case 'Accessories': accessories.remove(value); break;
      case 'Ear': ears.remove(value); break;
      case 'Eyebrows': eyebrows.remove(value); break;
      case 'Eyes': eyes.remove(value); break;
      case 'Equipment': equipment.remove(value); break;
      case 'Face': face.remove(value); break;
      case 'Pants': pants.remove(value); break;
      case 'Shirts': shirts.remove(value); break;
    }
  }

  void clearSelections() {
    bases.clear();
    heads.clear();
    hairs.clear();
    accessories.clear();
    ears.clear();
    eyebrows.clear();
    eyes.clear();
    equipment.clear();
    face.clear();
    pants.clear();
    shirts.clear();
  }
}

Future<Image> loadPng(String fileName) async {
  return Image.asset(fileName);
}


 CharacterCustomization fromMap(Map<String, dynamic> map) {
  return CharacterCustomization()
    ..bases = List<String>.from(map['bases'] ?? [])
    ..heads = List<String>.from(map['heads'] ?? [])
    ..hairs = List<String>.from(map['hairs'] ?? [])
    ..accessories = List<String>.from(map['accessories'] ?? [])
    ..ears = List<String>.from(map['ears'] ?? [])
    ..eyebrows = List<String>.from(map['eyebrows'] ?? [])
    ..eyes = List<String>.from(map['eyes'] ?? [])
    ..equipment = List<String>.from(map['equipment'] ?? [])
    ..face = List<String>.from(map['face'] ?? [])
    ..pants = List<String>.from(map['pants'] ?? [])
    ..shirts = List<String>.from(map['shirts'] ?? [])
    ..backgroundColor = Color(int.parse(map['backgroundColor'] ?? '0xffffffff', radix: 16));
}





