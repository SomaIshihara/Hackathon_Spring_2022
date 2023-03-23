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
 32;
 0.50000;-3.00000;0.50000;,
 -0.50000;-3.00000;0.50000;,
 -0.50000;-3.00000;-0.50000;,
 0.50000;-3.00000;-0.50000;,
 -0.50000;0.00000;0.50000;,
 0.50000;0.00000;0.50000;,
 -0.50000;0.00000;-0.50000;,
 0.50000;0.00000;-0.50000;,
 -0.50000;-1.00000;0.50000;,
 0.50000;-1.00000;0.50000;,
 -0.50000;-1.00000;0.50000;,
 0.50000;-1.00000;0.50000;,
 -0.50000;-1.00000;-0.50000;,
 0.50000;-1.00000;-0.50000;,
 -0.50000;-1.00000;-0.50000;,
 0.50000;-1.00000;-0.50000;,
 0.56250;-3.18750;0.56250;,
 -0.56250;-3.18750;-0.56250;,
 -0.56250;-3.18750;0.56250;,
 0.56250;-3.18750;-0.56250;,
 -0.56250;0.18750;0.56250;,
 -0.56250;0.18750;-0.56250;,
 0.56250;0.18750;0.56250;,
 0.56250;0.18750;-0.56250;,
 -0.56250;-0.93750;0.56250;,
 0.56250;-0.93750;0.56250;,
 0.56250;-0.93750;0.56250;,
 -0.56250;-0.93750;0.56250;,
 -0.56250;-0.93750;-0.56250;,
 0.56250;-0.93750;-0.56250;,
 -0.56250;-0.93750;-0.56250;,
 0.56250;-0.93750;-0.56250;;
 
 40;
 3;0,1,2;,
 3;3,0,2;,
 3;4,5,6;,
 3;5,7,6;,
 3;8,1,0;,
 3;9,8,0;,
 3;4,10,11;,
 3;5,4,11;,
 3;2,12,3;,
 3;12,13,3;,
 3;14,6,15;,
 3;6,7,15;,
 3;2,1,8;,
 3;14,10,4;,
 3;12,2,8;,
 3;6,14,4;,
 3;0,3,9;,
 3;11,15,5;,
 3;3,13,9;,
 3;15,7,5;,
 3;16,17,18;,
 3;19,17,16;,
 3;20,21,22;,
 3;22,21,23;,
 3;24,16,18;,
 3;25,16,24;,
 3;20,26,27;,
 3;22,26,20;,
 3;17,19,28;,
 3;28,19,29;,
 3;30,31,21;,
 3;21,31,23;,
 3;17,24,18;,
 3;30,20,27;,
 3;28,24,17;,
 3;21,20,30;,
 3;16,25,19;,
 3;26,22,31;,
 3;19,25,29;,
 3;31,22,23;;
 
 MeshMaterialList {
  2;
  40;
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "230323-0.png";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  28;
  0.000000;-1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  -0.000000;0.000000;-1.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;;
  40;
  3;0,0,0;,
  3;0,0,0;,
  3;1,1,1;,
  3;1,1,1;,
  3;2,4,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;5,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;6,6,7;,
  3;8,7,9;,
  3;8,6,7;,
  3;9,8,9;,
  3;10,10,11;,
  3;11,12,13;,
  3;10,12,11;,
  3;12,13,13;,
  3;14,14,14;,
  3;14,14,14;,
  3;15,15,15;,
  3;15,15,15;,
  3;16,16,18;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;19,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;20,21,20;,
  3;22,23,21;,
  3;22,21,20;,
  3;23,23,22;,
  3;24,25,24;,
  3;25,26,27;,
  3;24,25,27;,
  3;27,26,26;;
 }
 MeshTextureCoords {
  32;
  0.404297;0.500000;,
  0.404297;0.500000;,
  0.404297;0.500000;,
  0.404297;0.500000;,
  0.642578;0.500000;,
  0.642578;0.500000;,
  0.642578;0.500000;,
  0.642578;0.500000;,
  0.404297;0.500000;,
  0.404297;0.500000;,
  0.642578;0.500000;,
  0.642578;0.500000;,
  0.404297;0.500000;,
  0.404297;0.500000;,
  0.642578;0.500000;,
  0.642578;0.500000;,
  0.404297;0.500000;,
  0.404297;0.500000;,
  0.404297;0.500000;,
  0.404297;0.500000;,
  0.642578;0.500000;,
  0.642578;0.500000;,
  0.642578;0.500000;,
  0.642578;0.500000;,
  0.404297;0.500000;,
  0.404297;0.500000;,
  0.642578;0.500000;,
  0.642578;0.500000;,
  0.404297;0.500000;,
  0.404297;0.500000;,
  0.642578;0.500000;,
  0.642578;0.500000;;
 }
}
