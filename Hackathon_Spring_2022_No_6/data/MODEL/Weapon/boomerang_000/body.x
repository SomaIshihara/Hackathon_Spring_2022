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
 196;
 5.65685;1.00000;0.00000;,
 5.65685;0.00000;0.00000;,
 4.94975;0.00000;-0.70711;,
 4.94975;1.00000;-0.70711;,
 4.94975;0.00000;-0.70711;,
 4.24264;0.00000;-1.41421;,
 4.94975;1.00000;-0.70711;,
 4.24264;1.00000;-1.41421;,
 0.00000;1.00000;2.82843;,
 0.00000;0.00000;2.82843;,
 -2.12132;0.00000;0.70711;,
 -2.12132;1.00000;0.70711;,
 -2.12132;0.00000;0.70711;,
 -2.82843;0.00000;0.00000;,
 -2.12132;1.00000;0.70711;,
 -2.82843;1.00000;0.00000;,
 -2.82843;0.00000;0.00000;,
 -4.24264;0.00000;-1.41421;,
 -2.82843;1.00000;0.00000;,
 -4.24264;1.00000;-1.41421;,
 0.70711;0.00000;4.94975;,
 0.70711;1.00000;4.94975;,
 0.00000;0.00000;4.24264;,
 0.00000;1.00000;4.24264;,
 -0.70711;0.00000;4.94975;,
 -0.70711;1.00000;4.94975;,
 -3.53553;0.00000;2.12132;,
 -3.53553;0.00000;2.12132;,
 -3.53553;1.00000;2.12132;,
 -4.24264;0.00000;1.41421;,
 -3.53553;1.00000;2.12132;,
 -4.24264;0.00000;1.41421;,
 -4.24264;1.00000;1.41421;,
 -5.65685;0.00000;0.00000;,
 -4.24264;1.00000;1.41421;,
 -5.65685;1.00000;0.00000;,
 4.24264;0.00000;1.41421;,
 4.24264;1.00000;1.41421;,
 3.53553;0.00000;2.12132;,
 4.24264;0.00000;1.41421;,
 4.24264;1.00000;1.41421;,
 3.53553;1.00000;2.12132;,
 3.53553;0.00000;2.12132;,
 3.53553;1.00000;2.12132;,
 2.82843;0.00000;0.00000;,
 2.82843;1.00000;0.00000;,
 2.82843;0.00000;0.00000;,
 2.12132;0.00000;0.70711;,
 2.82843;1.00000;0.00000;,
 2.12132;1.00000;0.70711;,
 2.12132;0.00000;0.70711;,
 2.12132;1.00000;0.70711;,
 -4.94975;0.00000;-0.70711;,
 -4.94975;1.00000;-0.70711;,
 -4.94975;0.00000;-0.70711;,
 -4.94975;1.00000;-0.70711;,
 3.53553;0.00000;0.70711;,
 3.53553;0.00000;0.70711;,
 2.82843;0.00000;1.41421;,
 2.82843;0.00000;1.41421;,
 0.70711;0.00000;3.53553;,
 3.53553;0.00000;0.70711;,
 3.53553;0.00000;0.70711;,
 2.82843;0.00000;1.41421;,
 2.82843;0.00000;1.41421;,
 0.70711;0.00000;3.53553;,
 0.00000;0.00000;2.82843;,
 -0.70711;0.00000;3.53553;,
 -0.70711;0.00000;3.53553;,
 -2.82843;0.00000;1.41421;,
 -2.82843;0.00000;1.41421;,
 -2.82843;0.00000;1.41421;,
 -3.53553;0.00000;0.70711;,
 -2.82843;0.00000;1.41421;,
 -3.53553;0.00000;0.70711;,
 -3.53553;0.00000;0.70711;,
 -3.53553;0.00000;0.70711;,
 3.53553;1.00000;0.70711;,
 3.53553;1.00000;0.70711;,
 2.82843;1.00000;1.41421;,
 2.82843;1.00000;1.41421;,
 0.70711;1.00000;3.53553;,
 3.53553;1.00000;0.70711;,
 3.53553;1.00000;0.70711;,
 2.82843;1.00000;1.41421;,
 2.82843;1.00000;1.41421;,
 0.70711;1.00000;3.53553;,
 0.00000;1.00000;2.82843;,
 -0.70711;1.00000;3.53553;,
 -0.70711;1.00000;3.53553;,
 -2.82843;1.00000;1.41421;,
 -2.82843;1.00000;1.41421;,
 -2.82843;1.00000;1.41421;,
 -2.82843;1.00000;1.41421;,
 -3.53553;1.00000;0.70711;,
 -3.53553;1.00000;0.70711;,
 -3.53553;1.00000;0.70711;,
 -3.53553;1.00000;0.70711;,
 5.94615;1.02557;-0.09040;,
 5.20288;-0.02557;-0.83367;,
 5.94615;-0.02557;-0.09040;,
 5.20288;1.02557;-0.83367;,
 4.45961;-0.02557;-1.57694;,
 5.20288;-0.02557;-0.83367;,
 5.20288;1.02557;-0.83367;,
 4.45961;1.02557;-1.57694;,
 0.00000;1.02557;2.88267;,
 -2.22980;-0.02557;0.65286;,
 0.00000;-0.02557;2.88267;,
 -2.22980;1.02557;0.65286;,
 -2.97307;-0.02557;-0.09040;,
 -2.22980;-0.02557;0.65286;,
 -2.22980;1.02557;0.65286;,
 -2.97307;1.02557;-0.09040;,
 -4.45961;-0.02557;-1.57694;,
 -2.97307;-0.02557;-0.09040;,
 -2.97307;1.02557;-0.09040;,
 -4.45961;1.02557;-1.57694;,
 0.74327;-0.02557;5.11247;,
 0.00000;-0.02557;4.36921;,
 0.74327;1.02557;5.11247;,
 0.00000;1.02557;4.36921;,
 -0.74327;-0.02557;5.11247;,
 -3.71634;-0.02557;2.13940;,
 -0.74327;1.02557;5.11247;,
 -3.71634;-0.02557;2.13940;,
 -4.45961;-0.02557;1.39613;,
 -3.71634;1.02557;2.13940;,
 -3.71634;1.02557;2.13940;,
 -4.45961;-0.02557;1.39613;,
 -5.94615;-0.02557;-0.09040;,
 -4.45961;1.02557;1.39613;,
 -4.45961;1.02557;1.39613;,
 -5.94615;1.02557;-0.09040;,
 4.45961;-0.02557;1.39613;,
 4.45961;1.02557;1.39613;,
 3.71634;-0.02557;2.13940;,
 4.45961;1.02557;1.39613;,
 4.45961;-0.02557;1.39613;,
 3.71634;1.02557;2.13940;,
 3.71634;1.02557;2.13940;,
 3.71634;-0.02557;2.13940;,
 2.97307;-0.02557;-0.09040;,
 2.97307;1.02557;-0.09040;,
 2.97307;-0.02557;-0.09040;,
 2.97307;1.02557;-0.09040;,
 2.22980;-0.02557;0.65286;,
 2.22980;1.02557;0.65286;,
 2.22980;-0.02557;0.65286;,
 2.22980;1.02557;0.65286;,
 -5.20288;-0.02557;-0.83367;,
 -5.20288;1.02557;-0.83367;,
 -5.20288;-0.02557;-0.83367;,
 -5.20288;1.02557;-0.83367;,
 3.71634;-0.02557;0.65286;,
 3.71634;-0.02557;0.65286;,
 2.97307;-0.02557;1.39613;,
 2.97307;-0.02557;1.39613;,
 0.74327;-0.02557;3.62594;,
 3.71634;-0.02557;0.65286;,
 2.97307;-0.02557;1.39613;,
 3.71634;-0.02557;0.65286;,
 0.74327;-0.02557;3.62594;,
 2.97307;-0.02557;1.39613;,
 0.00000;-0.02557;2.88267;,
 -0.74327;-0.02557;3.62594;,
 -0.74327;-0.02557;3.62594;,
 -2.97307;-0.02557;1.39613;,
 -2.97307;-0.02557;1.39613;,
 -2.97307;-0.02557;1.39613;,
 -3.71634;-0.02557;0.65286;,
 -2.97307;-0.02557;1.39613;,
 -3.71634;-0.02557;0.65286;,
 -3.71634;-0.02557;0.65286;,
 -3.71634;-0.02557;0.65286;,
 3.71634;1.02557;0.65286;,
 3.71634;1.02557;0.65286;,
 2.97307;1.02557;1.39613;,
 2.97307;1.02557;1.39613;,
 0.74327;1.02557;3.62594;,
 3.71634;1.02557;0.65286;,
 3.71634;1.02557;0.65286;,
 2.97307;1.02557;1.39613;,
 2.97307;1.02557;1.39613;,
 0.74327;1.02557;3.62594;,
 0.00000;1.02557;2.88267;,
 -0.74327;1.02557;3.62594;,
 -0.74327;1.02557;3.62594;,
 -2.97307;1.02557;1.39613;,
 -2.97307;1.02557;1.39613;,
 -2.97307;1.02557;1.39613;,
 -2.97307;1.02557;1.39613;,
 -3.71634;1.02557;0.65286;,
 -3.71634;1.02557;0.65286;,
 -3.71634;1.02557;0.65286;,
 -3.71634;1.02557;0.65286;;
 
 184;
 3;0,1,2;,
 3;3,4,5;,
 3;6,0,2;,
 3;7,3,5;,
 3;8,9,10;,
 3;11,12,13;,
 3;14,8,10;,
 3;15,16,17;,
 3;18,11,13;,
 3;19,15,17;,
 3;20,21,22;,
 3;21,23,22;,
 3;24,25,26;,
 3;27,28,29;,
 3;25,30,26;,
 3;31,32,33;,
 3;28,34,29;,
 3;32,35,33;,
 3;36,1,0;,
 3;37,36,0;,
 3;38,39,40;,
 3;41,38,40;,
 3;20,42,43;,
 3;21,20,43;,
 3;24,22,23;,
 3;25,24,23;,
 3;5,44,7;,
 3;44,45,7;,
 3;46,47,48;,
 3;47,49,48;,
 3;50,9,51;,
 3;9,8,51;,
 3;17,52,19;,
 3;52,53,19;,
 3;54,33,55;,
 3;33,35,55;,
 3;2,1,36;,
 3;56,39,38;,
 3;57,2,36;,
 3;58,42,20;,
 3;59,56,38;,
 3;60,58,20;,
 3;22,60,20;,
 3;5,4,61;,
 3;46,62,63;,
 3;44,5,61;,
 3;50,64,65;,
 3;47,46,63;,
 3;66,22,24;,
 3;9,50,65;,
 3;66,60,22;,
 3;67,66,24;,
 3;10,9,68;,
 3;69,67,24;,
 3;70,10,68;,
 3;26,69,24;,
 3;13,12,71;,
 3;72,73,27;,
 3;74,13,71;,
 3;29,72,27;,
 3;17,16,75;,
 3;54,76,31;,
 3;52,17,75;,
 3;33,54,31;,
 3;0,6,37;,
 3;40,77,41;,
 3;6,78,37;,
 3;43,79,21;,
 3;77,80,41;,
 3;79,81,21;,
 3;81,23,21;,
 3;3,7,82;,
 3;83,48,84;,
 3;7,45,82;,
 3;85,51,86;,
 3;48,49,84;,
 3;23,87,25;,
 3;51,8,86;,
 3;81,87,23;,
 3;87,88,25;,
 3;8,14,89;,
 3;88,90,25;,
 3;14,91,89;,
 3;90,30,25;,
 3;11,18,92;,
 3;93,94,28;,
 3;18,95,92;,
 3;94,34,28;,
 3;15,19,96;,
 3;97,55,32;,
 3;19,53,96;,
 3;55,35,32;,
 3;98,99,100;,
 3;101,102,103;,
 3;104,99,98;,
 3;105,102,101;,
 3;106,107,108;,
 3;109,110,111;,
 3;112,107,106;,
 3;113,114,115;,
 3;116,110,109;,
 3;117,114,113;,
 3;118,119,120;,
 3;120,119,121;,
 3;122,123,124;,
 3;125,126,127;,
 3;124,123,128;,
 3;129,130,131;,
 3;127,126,132;,
 3;131,130,133;,
 3;134,98,100;,
 3;135,98,134;,
 3;136,137,138;,
 3;139,137,136;,
 3;118,140,141;,
 3;120,140,118;,
 3;122,121,119;,
 3;124,121,122;,
 3;102,105,142;,
 3;142,105,143;,
 3;144,145,146;,
 3;146,145,147;,
 3;148,149,108;,
 3;108,149,106;,
 3;114,117,150;,
 3;150,117,151;,
 3;152,153,130;,
 3;130,153,133;,
 3;99,134,100;,
 3;154,136,138;,
 3;155,134,99;,
 3;156,118,141;,
 3;157,136,154;,
 3;158,118,156;,
 3;119,118,158;,
 3;102,159,103;,
 3;144,160,161;,
 3;142,159,102;,
 3;148,162,163;,
 3;146,160,144;,
 3;164,122,119;,
 3;108,162,148;,
 3;164,119,158;,
 3;165,122,164;,
 3;107,166,108;,
 3;167,122,165;,
 3;168,166,107;,
 3;123,122,167;,
 3;110,169,111;,
 3;170,125,171;,
 3;172,169,110;,
 3;126,125,170;,
 3;114,173,115;,
 3;152,129,174;,
 3;150,173,114;,
 3;130,129,152;,
 3;98,135,104;,
 3;137,139,175;,
 3;104,135,176;,
 3;140,120,177;,
 3;175,139,178;,
 3;177,120,179;,
 3;179,120,121;,
 3;101,180,105;,
 3;181,182,145;,
 3;105,180,143;,
 3;183,184,149;,
 3;145,182,147;,
 3;121,124,185;,
 3;149,184,106;,
 3;179,121,185;,
 3;185,124,186;,
 3;106,187,112;,
 3;186,124,188;,
 3;112,187,189;,
 3;188,124,128;,
 3;109,190,116;,
 3;191,127,192;,
 3;116,190,193;,
 3;192,127,132;,
 3;113,194,117;,
 3;195,131,153;,
 3;117,194,151;,
 3;153,131,133;;
 
 MeshMaterialList {
  2;
  184;
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
    "data\\TEXTURE\\Material\\pallet0.png";
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
  64;
  0.707107;0.000000;-0.707107;,
  0.707107;0.000000;-0.707107;,
  0.707107;0.000000;-0.707107;,
  0.707107;0.000000;-0.707107;,
  0.707107;0.000000;-0.707107;,
  0.707107;0.000000;-0.707107;,
  0.707107;0.000000;-0.707107;,
  -0.707107;0.000000;0.707107;,
  -0.707107;0.000000;0.707107;,
  -0.707107;0.000000;0.707107;,
  -0.707107;0.000000;0.707107;,
  0.707107;0.000000;0.707107;,
  -0.707107;0.000000;-0.707107;,
  -0.707107;0.000000;-0.707107;,
  0.000000;-1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.707107;0.000000;0.707107;,
  0.707107;0.000000;0.707107;,
  0.707107;0.000000;0.707107;,
  -0.707107;0.000000;-0.707107;,
  -0.707107;0.000000;-0.707107;,
  -0.707107;0.000000;-0.707107;,
  -0.707107;0.000000;-0.707107;,
  -0.707107;0.000000;-0.707107;,
  -0.707107;0.000000;0.707107;,
  -0.707107;0.000000;0.707107;,
  -0.707107;0.000000;0.707107;,
  -0.707107;0.000000;0.707107;,
  -0.707107;0.000000;0.707107;,
  -0.707107;0.000000;0.707106;,
  -0.707107;0.000000;0.707107;,
  -0.707107;0.000000;0.707107;,
  -0.707107;0.000000;0.707106;,
  0.707107;0.000000;-0.707107;,
  0.707107;0.000000;-0.707107;,
  0.707107;0.000000;-0.707107;,
  0.707107;0.000000;-0.707107;,
  0.707107;0.000000;-0.707107;,
  0.707106;0.000000;-0.707107;,
  0.707107;0.000000;-0.707107;,
  0.707107;0.000000;-0.707107;,
  0.707106;-0.000000;-0.707107;,
  -0.707107;0.000000;-0.707107;,
  -0.707107;0.000000;-0.707107;,
  -0.707107;0.000000;-0.707107;,
  -0.707107;0.000000;-0.707107;,
  0.707107;0.000000;0.707107;,
  0.707107;0.000000;0.707107;,
  0.707107;0.000000;0.707107;,
  0.707107;0.000000;0.707107;,
  0.707107;0.000000;0.707107;,
  0.707107;0.000000;0.707107;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  -0.707106;0.000000;-0.707107;,
  -0.707106;0.000000;-0.707107;,
  -0.707107;0.000000;-0.707107;,
  -0.707107;0.000000;-0.707107;,
  -0.707107;0.000000;-0.707107;,
  0.707107;0.000000;0.707106;,
  0.707107;0.000000;0.707106;,
  0.707107;0.000000;0.707107;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;0.000000;;
  184;
  3;3,0,1;,
  3;4,1,2;,
  3;4,3,1;,
  3;5,4,2;,
  3;4,6,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;6,4,4;,
  3;7,8,8;,
  3;8,7,8;,
  3;9,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,9,10;,
  3;11,16,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;16,11,11;,
  3;17,18,17;,
  3;18,17,17;,
  3;19,12,12;,
  3;12,12,12;,
  3;12,12,12;,
  3;12,12,12;,
  3;12,12,12;,
  3;12,19,12;,
  3;20,12,21;,
  3;12,13,21;,
  3;12,22,13;,
  3;22,23,13;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;27,25,24;,
  3;28,26,25;,
  3;28,25,27;,
  3;26,26,28;,
  3;26,27,26;,
  3;30,24,27;,
  3;30,27,26;,
  3;31,29,24;,
  3;31,24,30;,
  3;32,29,31;,
  3;33,34,34;,
  3;34,34,33;,
  3;35,36,35;,
  3;36,37,39;,
  3;35,36,39;,
  3;37,38,40;,
  3;39,37,40;,
  3;40,38,41;,
  3;42,54,55;,
  3;43,54,42;,
  3;44,43,42;,
  3;45,43,44;,
  3;56,45,44;,
  3;56,45,56;,
  3;57,57,58;,
  3;58,57,57;,
  3;59,60,46;,
  3;46,60,47;,
  3;46,47,48;,
  3;48,47,49;,
  3;48,49,61;,
  3;61,49,61;,
  3;61,61,50;,
  3;50,61,51;,
  3;50,51,49;,
  3;49,51,47;,
  3;52,52,62;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;62,52,52;,
  3;63,53,53;,
  3;53,53,53;,
  3;53,53,53;,
  3;53,53,53;,
  3;53,53,53;,
  3;53,53,53;,
  3;53,53,53;,
  3;53,53,53;,
  3;53,53,53;,
  3;53,53,53;,
  3;53,53,53;,
  3;53,53,53;,
  3;53,53,53;,
  3;53,53,53;,
  3;53,53,53;,
  3;53,53,53;,
  3;53,53,53;,
  3;53,53,53;,
  3;53,53,53;,
  3;53,53,53;,
  3;53,53,53;,
  3;53,53,53;,
  3;53,53,53;,
  3;53,53,53;,
  3;53,53,53;,
  3;53,53,53;,
  3;53,53,53;,
  3;53,53,63;;
 }
 MeshTextureCoords {
  196;
  0.712891;0.500000;,
  0.712891;0.500000;,
  0.712891;0.500000;,
  0.708984;0.500000;,
  0.708984;0.500000;,
  0.708984;0.500000;,
  0.712891;0.500000;,
  0.708984;0.500000;,
  0.693359;0.500000;,
  0.693359;0.500000;,
  0.693359;0.500000;,
  0.759766;0.500000;,
  0.759766;0.500000;,
  0.759766;0.500000;,
  0.693359;0.500000;,
  0.708984;0.500000;,
  0.708984;0.500000;,
  0.708984;0.500000;,
  0.759766;0.500000;,
  0.708984;0.500000;,
  0.697266;0.500000;,
  0.697266;0.500000;,
  0.697266;0.500000;,
  0.697266;0.500000;,
  0.697266;0.500000;,
  0.697266;0.500000;,
  0.697266;0.500000;,
  0.763672;0.500000;,
  0.763672;0.500000;,
  0.763672;0.500000;,
  0.697266;0.500000;,
  0.712891;0.500000;,
  0.712891;0.500000;,
  0.712891;0.500000;,
  0.763672;0.500000;,
  0.712891;0.500000;,
  0.712891;0.500000;,
  0.712891;0.500000;,
  0.763672;0.500000;,
  0.763672;0.500000;,
  0.763672;0.500000;,
  0.763672;0.500000;,
  0.697266;0.500000;,
  0.697266;0.500000;,
  0.708984;0.500000;,
  0.708984;0.500000;,
  0.759766;0.500000;,
  0.759766;0.500000;,
  0.759766;0.500000;,
  0.759766;0.500000;,
  0.693359;0.500000;,
  0.693359;0.500000;,
  0.708984;0.500000;,
  0.708984;0.500000;,
  0.712891;0.500000;,
  0.712891;0.500000;,
  0.763672;0.500000;,
  0.712891;0.500000;,
  0.697266;0.500000;,
  0.763672;0.500000;,
  0.697266;0.500000;,
  0.708984;0.500000;,
  0.759766;0.500000;,
  0.759766;0.500000;,
  0.693359;0.500000;,
  0.693359;0.500000;,
  0.697266;0.500000;,
  0.697266;0.500000;,
  0.693359;0.500000;,
  0.697266;0.500000;,
  0.693359;0.500000;,
  0.759766;0.500000;,
  0.763672;0.500000;,
  0.763672;0.500000;,
  0.759766;0.500000;,
  0.708984;0.500000;,
  0.712891;0.500000;,
  0.763672;0.500000;,
  0.712891;0.500000;,
  0.697266;0.500000;,
  0.763672;0.500000;,
  0.697266;0.500000;,
  0.708984;0.500000;,
  0.759766;0.500000;,
  0.759766;0.500000;,
  0.693359;0.500000;,
  0.693359;0.500000;,
  0.697266;0.500000;,
  0.697266;0.500000;,
  0.693359;0.500000;,
  0.697266;0.500000;,
  0.693359;0.500000;,
  0.759766;0.500000;,
  0.763672;0.500000;,
  0.763672;0.500000;,
  0.759766;0.500000;,
  0.708984;0.500000;,
  0.712891;0.500000;,
  0.712891;0.500000;,
  0.712891;0.500000;,
  0.712891;0.500000;,
  0.708984;0.500000;,
  0.708984;0.500000;,
  0.708984;0.500000;,
  0.712891;0.500000;,
  0.708984;0.500000;,
  0.693359;0.500000;,
  0.693359;0.500000;,
  0.693359;0.500000;,
  0.759766;0.500000;,
  0.759766;0.500000;,
  0.759766;0.500000;,
  0.693359;0.500000;,
  0.708984;0.500000;,
  0.708984;0.500000;,
  0.708984;0.500000;,
  0.759766;0.500000;,
  0.708984;0.500000;,
  0.697266;0.500000;,
  0.697266;0.500000;,
  0.697266;0.500000;,
  0.697266;0.500000;,
  0.697266;0.500000;,
  0.697266;0.500000;,
  0.697266;0.500000;,
  0.763672;0.500000;,
  0.763672;0.500000;,
  0.763672;0.500000;,
  0.697266;0.500000;,
  0.712891;0.500000;,
  0.712891;0.500000;,
  0.712891;0.500000;,
  0.763672;0.500000;,
  0.712891;0.500000;,
  0.712891;0.500000;,
  0.712891;0.500000;,
  0.763672;0.500000;,
  0.763672;0.500000;,
  0.763672;0.500000;,
  0.763672;0.500000;,
  0.697266;0.500000;,
  0.697266;0.500000;,
  0.708984;0.500000;,
  0.708984;0.500000;,
  0.759766;0.500000;,
  0.759766;0.500000;,
  0.759766;0.500000;,
  0.759766;0.500000;,
  0.693359;0.500000;,
  0.693359;0.500000;,
  0.708984;0.500000;,
  0.708984;0.500000;,
  0.712891;0.500000;,
  0.712891;0.500000;,
  0.763672;0.500000;,
  0.712891;0.500000;,
  0.697266;0.500000;,
  0.763672;0.500000;,
  0.697266;0.500000;,
  0.708984;0.500000;,
  0.759766;0.500000;,
  0.759766;0.500000;,
  0.693359;0.500000;,
  0.693359;0.500000;,
  0.697266;0.500000;,
  0.697266;0.500000;,
  0.693359;0.500000;,
  0.697266;0.500000;,
  0.693359;0.500000;,
  0.759766;0.500000;,
  0.763672;0.500000;,
  0.763672;0.500000;,
  0.759766;0.500000;,
  0.708984;0.500000;,
  0.712891;0.500000;,
  0.763672;0.500000;,
  0.712891;0.500000;,
  0.697266;0.500000;,
  0.763672;0.500000;,
  0.697266;0.500000;,
  0.708984;0.500000;,
  0.759766;0.500000;,
  0.759766;0.500000;,
  0.693359;0.500000;,
  0.693359;0.500000;,
  0.697266;0.500000;,
  0.697266;0.500000;,
  0.693359;0.500000;,
  0.697266;0.500000;,
  0.693359;0.500000;,
  0.759766;0.500000;,
  0.763672;0.500000;,
  0.763672;0.500000;,
  0.759766;0.500000;,
  0.708984;0.500000;,
  0.712891;0.500000;;
 }
}
