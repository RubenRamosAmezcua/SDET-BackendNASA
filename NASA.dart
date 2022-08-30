import 'dart:convert';
import 'dart:io';

import 'package:flutter/cupertino.dart';
import 'package:dio/dio.dart';
import 'package:http/http.dart' as http;
import 'package:flutter_stripe/flutter_stripe.dart';

class Nasa{
  static const My_KEY ="pXI0cr8DdRgEmMHuWQz8WxitLjegXkSW9HSZldyx";
  static const NASA_1000thMarssol = "https://api.nasa.gov/mars-photos/api/v1/rovers/curiosity/photos?sol=1000&api_key=pXI0cr8DdRgEmMHuWQz8WxitLjegXkSW9HSZldyx";
  static const NASA_Earth = "https://api.nasa.gov/mars-photos/api/v1/rovers/curiosity/photos?earth_date=";
  static const NASA_1000_Opportunity = "https://api.nasa.gov/mars-photos/api/v1/rovers/opportunity/photos?sol=1000&api_key=";
  static const NASA_Spirit = "https://api.nasa.gov/mars-photos/api/v1/rovers/spirit/photos?sol=1000&api_key=";
  static const NASA_1000cameras = "https://api.nasa.gov/mars-photos/api/v1/rovers/curiosity/photos?sol=1000&camera=";
  String date = "";
  var mars =[""];
  var earth =[""];
  var resultcomp =[""];
  var cameracur =[""];
  var cameras  =["FHAZ","RHAZ","MASTCHEMCAM", "MAHLI", "MARDI",	"NAVCAM","PANCAM","MINITES"];
  var resultvalidation  = [""];
  var validation ;
  var ascending =[""];
  var descending =[""];
  int a;
  int b;





  //Get the 10 picst from the URL 1000 Mars sol
  Future<String>Query10pics1000Marssol() async{
    try{
      final response =await http.get(
          Uri.parse(NASA_1000thMarssol),

      ).then((response)async{
        String Marsphotos = jsonDecode(response.body).slice(0,10);

        return  Marsphotos;
      }).catchError((err){
        return 'Error $err';
      });
    }catch(e){return null;}
  }
///////////////////////////////////////////////////////////////Get the Earth date //////////////////////////////////////////////////////////

  Future<String>QueryEARTHDate() async{
    try{
      final response =await http.get(
        Uri.parse(NASA_1000thMarssol),

      ).then((response)async{
        String date = jsonDecode(response.body)['earth_date'];
        return date;
      }).catchError((err){
        return 'Error $err';
      });
    }catch(e){return null;}

  }
///////////////////////////////////////////////////////////////Get the pictures from the earth date//////////////////////////////////////////////////////////////////
  Future<String>QueryEARTHDate2() async{
    try{
      final response =await http.get(
        Uri.parse(NASA_Earth + date + My_KEY),

      ).then((response)async{
        String Earthphotos = jsonDecode(response.body).slice(0,10);
        return Earthphotos;
      }).catchError((err){
        return 'Error $err';
      });
    }catch(e){return null;}

  }
////////////////////////////////////////////////////////////////Comparing 1000Mars against Earth date picture///////////////////////////////////////////////////////////
  Future<String>Comparisons() async {
    for (int i = 0; i < 10; i++){
/////////////////////////////Getting the pictures from 1000Mars sol//////////////////////////////////
      try {
        final response = await http.get(
          Uri.parse(NASA_1000thMarssol),

        ).then((response) async {
          /////////////////////////////////////Storing data on a Matrix//////////////////////////////////////
           mars[i] = jsonDecode(response.body).slice(0,i);
          return date;
        }).catchError((err) {
          return 'Error $err';
        });
      } catch (e) {
        return null;
      }
      /////////////////////////////Getting the pictures from Earth date//////////////////////////////////
      try {
        final response = await http.get(
          Uri.parse(NASA_Earth + date + My_KEY),

        ).then((response) async {
          /////////////////////////////////////Storing data on a Matrix//////////////////////////////////////
          earth[i] = jsonDecode(response.body).slice(0,i);
          return date;
        }).catchError((err) {
          return 'Error $err';
        });
      } catch (e) {
        return null;
      }
////////////////////////////////////Making the comparison //////////////////////////////////////////////
      if (mars[i] == earth[i])
        {
          resultcomp[i]="Yes";
        }
      else {resultcomp[i]="Not the same"; }

  }
  }
  /////////////////////////////////////Validation no camera takes more than 10 times pictures than other/////////////////////////////////////////////////
  Future<String>Validation() async {
    for (int i = 0; i < 8; i++) {
      try {
        final response = await http.get(
          /////////////////////////////////////////calling the data for 1000 Mars on each camera and storing the data on a matrix
          Uri.parse(NASA_1000cameras + cameras[i] + My_KEY),

        ).then((response) async {

          cameracur [i] = jsonDecode(response.body);
          return cameracur [i];
        }).catchError((err) {
          return 'Error $err';
        });
      } catch (e) {
        return null;

      }
      //////////////////////////////////////recoding the data to a Json to get the length///////////////////////
      resultvalidation[i] = jsonDecode(cameracur[i]).length;
      /////////////////////////////////////sorting the data to descending order////////////////////////////////
      ascending = resultvalidation..sort();
      descending = ascending.reversed;

      ///////////////////////////////////diving by between the numbers (the first one is the highest so it will not change)/////////////////////////////
      for (int i = 0; i < 7; i++) {
        a = (descending[0] as int);
        b = (descending[i+1] as int);
        ///////////////////////////////////////the result must be less than 10 /////////////////////////////////////////////////////////////////////
        if (a/b>= 10 ){print ("There is a camera taking more than 10 times picture than other");}
          else {print ("No issues found");}



      }
      }

     }








}