xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 152;
 4.00000;1.00000;-1.00000;,
 4.00000;0.00000;4.00000;,
 4.00000;0.00000;-4.00000;,
 4.00000;1.00000;-2.00000;,
 4.00000;2.00000;2.00000;,
 4.00000;2.00000;1.00000;,
 4.00000;2.00000;-1.00000;,
 4.00000;1.00000;-1.00000;,
 4.00000;1.00000;-2.00000;,
 4.00000;2.00000;-1.00000;,
 4.00000;2.00000;-2.00000;,
 4.00000;2.00000;-2.00000;,
 4.00000;3.00000;2.00000;,
 4.00000;2.00000;2.00000;,
 4.00000;2.00000;1.00000;,
 4.00000;3.00000;2.00000;,
 4.00000;3.00000;1.00000;,
 4.00000;3.00000;1.00000;,
 4.00000;3.00000;-2.00000;,
 4.00000;3.00000;-3.00000;,
 4.00000;4.00000;-2.00000;,
 4.00000;4.00000;-2.00000;,
 4.00000;3.00000;-2.00000;,
 4.00000;3.00000;-3.00000;,
 4.00000;4.00000;-3.00000;,
 4.00000;4.00000;-3.00000;,
 4.00000;6.00000;2.00000;,
 4.00000;6.00000;1.00000;,
 4.00000;7.00000;2.00000;,
 4.00000;7.00000;2.00000;,
 4.00000;6.00000;2.00000;,
 4.00000;6.00000;1.00000;,
 4.00000;7.00000;1.00000;,
 4.00000;7.00000;1.00000;,
 4.00000;8.00000;4.00000;,
 4.00000;8.00000;-4.00000;,
 -4.00000;0.00000;4.00000;,
 -4.00000;1.00000;-1.00000;,
 -4.00000;0.00000;-4.00000;,
 -4.00000;1.00000;-2.00000;,
 -4.00000;2.00000;3.00000;,
 -4.00000;2.00000;2.00000;,
 -4.00000;1.00000;-1.00000;,
 -4.00000;2.00000;-1.00000;,
 -4.00000;1.00000;-2.00000;,
 -4.00000;2.00000;-1.00000;,
 -4.00000;2.00000;-2.00000;,
 -4.00000;2.00000;-2.00000;,
 -4.00000;2.00000;3.00000;,
 -4.00000;3.00000;3.00000;,
 -4.00000;2.00000;2.00000;,
 -4.00000;3.00000;3.00000;,
 -4.00000;3.00000;2.00000;,
 -4.00000;3.00000;2.00000;,
 -4.00000;4.00000;1.00000;,
 -4.00000;4.00000;0.00000;,
 -4.00000;5.00000;1.00000;,
 -4.00000;4.00000;1.00000;,
 -4.00000;5.00000;1.00000;,
 -4.00000;4.00000;0.00000;,
 -4.00000;5.00000;0.00000;,
 -4.00000;5.00000;0.00000;,
 -4.00000;6.00000;-2.00000;,
 -4.00000;6.00000;-3.00000;,
 -4.00000;7.00000;-2.00000;,
 -4.00000;6.00000;-2.00000;,
 -4.00000;7.00000;-2.00000;,
 -4.00000;6.00000;-3.00000;,
 -4.00000;7.00000;-3.00000;,
 -4.00000;7.00000;-3.00000;,
 -4.00000;8.00000;4.00000;,
 -4.00000;8.00000;-4.00000;,
 3.00000;2.00000;4.00000;,
 3.00000;3.00000;4.00000;,
 2.00000;2.00000;4.00000;,
 2.00000;2.00000;4.00000;,
 3.00000;2.00000;4.00000;,
 3.00000;3.00000;4.00000;,
 2.00000;3.00000;4.00000;,
 2.00000;3.00000;4.00000;,
 1.00000;1.00000;4.00000;,
 1.00000;2.00000;4.00000;,
 1.00000;5.00000;4.00000;,
 1.00000;6.00000;4.00000;,
 0.00000;1.00000;4.00000;,
 1.00000;1.00000;4.00000;,
 1.00000;2.00000;4.00000;,
 0.00000;1.00000;4.00000;,
 0.00000;2.00000;4.00000;,
 0.00000;2.00000;4.00000;,
 0.00000;5.00000;4.00000;,
 1.00000;5.00000;4.00000;,
 1.00000;6.00000;4.00000;,
 0.00000;5.00000;4.00000;,
 0.00000;6.00000;4.00000;,
 0.00000;6.00000;4.00000;,
 -2.00000;3.00000;4.00000;,
 -2.00000;4.00000;4.00000;,
 -3.00000;3.00000;4.00000;,
 -3.00000;3.00000;4.00000;,
 -2.00000;3.00000;4.00000;,
 -2.00000;4.00000;4.00000;,
 -3.00000;4.00000;4.00000;,
 -3.00000;4.00000;4.00000;,
 3.00000;6.00000;-4.00000;,
 3.00000;7.00000;-4.00000;,
 2.00000;2.00000;-4.00000;,
 2.00000;3.00000;-4.00000;,
 3.00000;6.00000;-4.00000;,
 2.00000;6.00000;-4.00000;,
 3.00000;7.00000;-4.00000;,
 2.00000;6.00000;-4.00000;,
 2.00000;7.00000;-4.00000;,
 2.00000;7.00000;-4.00000;,
 2.00000;2.00000;-4.00000;,
 1.00000;2.00000;-4.00000;,
 2.00000;3.00000;-4.00000;,
 1.00000;2.00000;-4.00000;,
 1.00000;3.00000;-4.00000;,
 1.00000;3.00000;-4.00000;,
 0.00000;1.00000;-4.00000;,
 0.00000;2.00000;-4.00000;,
 0.00000;5.00000;-4.00000;,
 0.00000;6.00000;-4.00000;,
 0.00000;1.00000;-4.00000;,
 -1.00000;1.00000;-4.00000;,
 0.00000;2.00000;-4.00000;,
 -1.00000;1.00000;-4.00000;,
 -1.00000;2.00000;-4.00000;,
 -1.00000;2.00000;-4.00000;,
 0.00000;5.00000;-4.00000;,
 -1.00000;5.00000;-4.00000;,
 0.00000;6.00000;-4.00000;,
 -1.00000;5.00000;-4.00000;,
 -1.00000;6.00000;-4.00000;,
 -1.00000;6.00000;-4.00000;,
 -2.00000;3.00000;-4.00000;,
 -2.00000;4.00000;-4.00000;,
 -3.00000;3.00000;-4.00000;,
 -2.00000;3.00000;-4.00000;,
 -3.00000;3.00000;-4.00000;,
 -2.00000;4.00000;-4.00000;,
 -3.00000;4.00000;-4.00000;,
 -3.00000;4.00000;-4.00000;,
 3.00000;0.00000;3.00000;,
 -3.00000;0.00000;3.00000;,
 3.00000;0.00000;-3.00000;,
 3.00000;0.00000;-3.00000;,
 3.00000;0.00000;3.00000;,
 -3.00000;0.00000;3.00000;,
 -3.00000;0.00000;-3.00000;,
 -3.00000;0.00000;-3.00000;;
 
 156;
 3;0,1,2;,
 3;3,0,2;,
 3;4,1,0;,
 3;5,4,0;,
 3;6,7,8;,
 3;9,5,0;,
 3;10,3,2;,
 3;11,6,8;,
 3;12,13,14;,
 3;15,1,4;,
 3;16,5,9;,
 3;17,12,14;,
 3;16,9,10;,
 3;18,10,2;,
 3;18,16,10;,
 3;19,18,2;,
 3;20,15,16;,
 3;20,16,18;,
 3;21,22,23;,
 3;24,19,2;,
 3;25,21,23;,
 3;26,1,15;,
 3;26,15,20;,
 3;26,20,24;,
 3;27,26,24;,
 3;28,1,26;,
 3;29,30,31;,
 3;32,27,24;,
 3;33,29,31;,
 3;34,1,28;,
 3;34,28,32;,
 3;35,24,2;,
 3;35,34,32;,
 3;35,32,24;,
 3;36,37,38;,
 3;37,39,38;,
 3;36,40,37;,
 3;40,41,37;,
 3;42,43,44;,
 3;41,45,37;,
 3;39,46,38;,
 3;43,47,44;,
 3;48,49,50;,
 3;36,51,40;,
 3;41,52,45;,
 3;49,53,50;,
 3;45,52,46;,
 3;51,54,52;,
 3;52,54,46;,
 3;54,55,46;,
 3;51,56,54;,
 3;57,58,59;,
 3;55,60,46;,
 3;58,61,59;,
 3;46,62,38;,
 3;60,62,46;,
 3;56,62,60;,
 3;62,63,38;,
 3;56,64,62;,
 3;65,66,67;,
 3;63,68,38;,
 3;66,69,67;,
 3;36,70,51;,
 3;51,70,56;,
 3;64,70,68;,
 3;56,70,64;,
 3;68,71,38;,
 3;70,71,68;,
 3;72,1,34;,
 3;73,72,34;,
 3;74,1,72;,
 3;75,76,77;,
 3;78,73,34;,
 3;79,75,77;,
 3;80,1,74;,
 3;80,74,78;,
 3;81,80,78;,
 3;82,78,34;,
 3;82,81,78;,
 3;83,82,34;,
 3;84,85,86;,
 3;87,1,80;,
 3;88,81,82;,
 3;89,84,86;,
 3;90,91,92;,
 3;93,88,82;,
 3;94,83,34;,
 3;95,90,92;,
 3;96,88,93;,
 3;96,87,88;,
 3;96,93,94;,
 3;97,96,94;,
 3;98,87,96;,
 3;99,100,101;,
 3;102,97,94;,
 3;103,99,101;,
 3;36,1,87;,
 3;36,87,98;,
 3;36,98,102;,
 3;70,94,34;,
 3;70,36,102;,
 3;70,102,94;,
 3;2,104,35;,
 3;104,105,35;,
 3;2,106,104;,
 3;106,107,104;,
 3;108,109,110;,
 3;107,111,104;,
 3;105,112,35;,
 3;109,113,110;,
 3;114,115,116;,
 3;2,117,106;,
 3;107,118,111;,
 3;115,119,116;,
 3;111,118,112;,
 3;2,120,117;,
 3;117,120,118;,
 3;120,121,118;,
 3;118,122,112;,
 3;121,122,118;,
 3;122,123,112;,
 3;124,125,126;,
 3;2,127,120;,
 3;121,128,122;,
 3;125,129,126;,
 3;130,131,132;,
 3;128,133,122;,
 3;123,134,112;,
 3;131,135,132;,
 3;128,136,133;,
 3;127,136,128;,
 3;133,136,134;,
 3;136,137,134;,
 3;127,138,136;,
 3;139,140,141;,
 3;137,142,134;,
 3;140,143,141;,
 3;2,38,127;,
 3;127,38,138;,
 3;138,38,142;,
 3;134,71,112;,
 3;38,71,142;,
 3;112,71,35;,
 3;142,71,134;,
 3;144,1,36;,
 3;145,144,36;,
 3;146,1,144;,
 3;147,148,149;,
 3;150,145,36;,
 3;151,147,149;,
 3;2,1,146;,
 3;2,146,150;,
 3;38,150,36;,
 3;38,2,150;,
 3;34,35,70;,
 3;35,71,70;;
 
 MeshMaterialList {
  1;
  156;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\Material\\pallet0.png";
   }
  }
 }
 MeshNormals {
  6;
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;-1.000000;,
  -0.000000;-1.000000;0.000000;,
  0.000000;1.000000;0.000000;;
  156;
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;5,5,5;,
  3;5,5,5;;
 }
 MeshTextureCoords {
  152;
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.369141;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.365234;0.500000;,
  0.369141;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.365234;0.500000;,
  0.369141;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.369141;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.365234;0.500000;,
  0.369141;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.365234;0.500000;,
  0.369141;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.365234;0.500000;,
  0.369141;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.369141;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.365234;0.500000;,
  0.369141;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.369141;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.369141;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.365234;0.500000;,
  0.369141;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.365234;0.500000;,
  0.361328;0.500000;,
  0.361328;0.500000;,
  0.361328;0.500000;,
  0.365234;0.500000;,
  0.361328;0.500000;;
 }
}