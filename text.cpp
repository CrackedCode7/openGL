#include "text.h"

#include <string>


Text::Text(float xPos, float yPos, float ySize, std::string text)
{   
    for (int i=0; i<26; i++)
    {
        textureMap[char(65+i)] = std::vector<int> {16*i, 504};
    }
    
    
    this -> text = text;
    length = text.length();

    float xSize = ySize*9/16;

    for (int i=0; i<length; i++)
    {
        vertices.push_back(xPos+i*xSize);
        vertices.push_back(yPos-ySize);
        vertices.push_back(0.0f);

        vertices.push_back(xPos+i*xSize+xSize);
        vertices.push_back(yPos-ySize);
        vertices.push_back(0.0f);

        vertices.push_back(xPos+i*xSize+xSize);
        vertices.push_back(yPos);
        vertices.push_back(0.0f);

        vertices.push_back(xPos+i*xSize);
        vertices.push_back(yPos);
        vertices.push_back(0.0f);


        indices.push_back(i*4);
        indices.push_back(i*4+1);
        indices.push_back(i*4+2);
        indices.push_back(i*4);
        indices.push_back(i*4+2);
        indices.push_back(i*4+3);


        texCoords.push_back(textureMap[text[i]][0]/512);
        texCoords.push_back((512-textureMap[text[i]][1]-16)/512);
        texCoords.push_back((textureMap[text[i]][0]+16)/512);
        texCoords.push_back((512-textureMap[text[i]][1]-16)/512);
        texCoords.push_back((textureMap[text[i]][0]+16)/512);
        texCoords.push_back((512-textureMap[text[i]][1])/512);
        texCoords.push_back(textureMap[text[i]][0]/512);
        texCoords.push_back((512-textureMap[text[i]][1])/512);
    }
}