#pragma once
#include <vector>
using std::string;
using std::vector;
class GeometryGroup{
    private:
        GLuint programID;
        GLuint vertexBuffer;
        GLuint vertices;
    public:


        GeometryGroup(const vector<float> vertexArray, const string vertexShader, const string fragmentShader){
            compileShaderProgram(vertexShader, fragmentShader);
            prepareVertexBuffer( vertexArray );
        };
        const GLuint getProgramID(){ 
            return programID; 
        }; 
        const GLuint getAmount(){
            return vertices;
        };
        const GLuint getVertexBuffer(){ return vertexBuffer; };
        virtual ~GeometryGroup(){
        }
                                                   
    private:
        int max(int a, int b){
            return a>b?a:b;
        };
        void prepareVertexBuffer(std::vector<float> array){
            vertices = array.size()/ 3.0;
            glGenBuffers(1, &vertexBuffer);
            std :: cout << "Buffer generated: "<< vertexBuffer << std::endl;
            glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * array.size() , &array[0], GL_STATIC_DRAW);
        };

        void compileShaderProgram(string vertexShader, string fragmentShader){
            GLint Result = GL_FALSE;
            int InfoLogLength;
            GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
            GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
            const char* vshader =   vertexShader.c_str();
            glShaderSource(VertexShaderID, 1, &vshader , NULL);
            glCompileShader(VertexShaderID);

            glGetShaderiv(VertexShaderID , GL_COMPILE_STATUS, &Result);
            glGetShaderiv(VertexShaderID , GL_INFO_LOG_LENGTH, &InfoLogLength);
            std::vector<char> VertexShaderErrorMessage(InfoLogLength);
            glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
            
            char const * FragmentSourcePointer = fragmentShader.c_str();
            glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
            glCompileShader(FragmentShaderID);
         
            glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
            glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

            std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
            glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
            fprintf(stdout,"%s\n", &FragmentShaderErrorMessage[0]);

            std::cout <<  "Linking program" << std:: endl;
            programID = glCreateProgram();
            glAttachShader(programID, VertexShaderID);
            glAttachShader(programID, FragmentShaderID);
            glLinkProgram(programID);

            glGetProgramiv(programID, GL_LINK_STATUS, &Result);
            glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
            std::vector<char> ProgramErrorMessage( max(InfoLogLength, int(1)) );
            glGetProgramInfoLog(programID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
            fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

            glDeleteShader(VertexShaderID);
            glDeleteShader(FragmentShaderID);
        };
};
