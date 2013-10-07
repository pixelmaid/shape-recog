/*
 GRT MIT License
 Copyright (c) <2012> <Nicholas Gillian, Media Lab, MIT>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
 and associated documentation files (the "Software"), to deal in the Software without restriction, 
 including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, 
 subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all copies or substantial 
 portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT 
 LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
 WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
 SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "MovingAverageFilter.h"

namespace GRT{
    
//Register the MovingAverageFilter module with the PreProcessing base class
RegisterPreProcessingModule< MovingAverageFilter > MovingAverageFilter::registerModule("MovingAverageFilter");

MovingAverageFilter::MovingAverageFilter(UINT filterSize,UINT numDimensions){
    preProcessingType = "MovingAverageFilter";
    debugLog.setProceedingText("[DEBUG MOVING AVERAGE FILTER]");
    errorLog.setProceedingText("[ERROR MOVING AVERAGE FILTER]");
    warningLog.setProceedingText("[WARNING MOVING AVERAGE FILTER]");
    init(filterSize,numDimensions);
}
    
MovingAverageFilter::MovingAverageFilter(const MovingAverageFilter &rhs){
    preProcessingType = "MovingAverageFilter";
    debugLog.setProceedingText("[DEBUG MOVING AVERAGE FILTER]");
    errorLog.setProceedingText("[ERROR MOVING AVERAGE FILTER]");
    warningLog.setProceedingText("[WARNING MOVING AVERAGE FILTER]");
    
    //Zero this instance
    this->filterSize = 0;
    this->inputSampleCounter = 0;
    
    //Copy from the rhs instance if needed
    if( rhs.initialized ){
        this->init( rhs.filterSize, rhs.numInputDimensions );
        this->dataBuffer = rhs.dataBuffer;
    }
    
    //Copy the base variables
    copyBaseVariables( (PreProcessing*)&rhs );
}
    
MovingAverageFilter::~MovingAverageFilter(){

}
    
MovingAverageFilter& MovingAverageFilter::operator=(const MovingAverageFilter &rhs){
    if(this!=&rhs){
        //Clear this instance
        this->filterSize = 0;
        this->inputSampleCounter = 0;
        this->dataBuffer.clear();
        
        //Copy from the rhs instance
        if( rhs.initialized ){
            this->init( rhs.filterSize, rhs.numInputDimensions );
            this->dataBuffer = rhs.dataBuffer;
        }
        
        //Copy the preprocessing base variables
        copyBaseVariables( (PreProcessing*)&rhs );
    }
    return *this;
}
    
bool MovingAverageFilter::clone(const PreProcessing *preProcessing){
    
    if( preProcessing == NULL ) return false;
    
    if( this->getPreProcessingType() == preProcessing->getPreProcessingType() ){
        
        MovingAverageFilter *ptr = (MovingAverageFilter*)preProcessing;
        //Clone the MovingAverageFilter values 
        this->filterSize = ptr->filterSize;
        this->inputSampleCounter = ptr->inputSampleCounter;
        this->dataBuffer = ptr->dataBuffer;
        
        //Copy the preprocessing base variables
        return copyBaseVariables( preProcessing );
    }
    
    errorLog << "clone(const PreProcessing *preProcessing) -  PreProcessing Types Do Not Match!" << endl;
    
    return false;
}

    
bool MovingAverageFilter::process(const vector< double > &inputVector){
    
#ifdef GRT_SAFE_CHECKING
    if( !initialized ){
        errorLog << "process(const vector< double > &inputVector) - The filter has not been initialized!" << endl;
        return false;
    }

    if( inputVector.size() != numInputDimensions ){
        errorLog << "process(const vector< double > &inputVector) - The size of the inputVector (" << inputVector.size() << ") does not match that of the filter (" << numInputDimensions << ")!" << endl;
        return false;
    }
#endif
    
    filter( inputVector );
    
    if( processedData.size() == numOutputDimensions ) return true;
    return false;

}

bool MovingAverageFilter::reset(){
    if( initialized ) return init(filterSize,numInputDimensions);
    return false;
}
    
bool MovingAverageFilter::saveSettingsToFile(string filename){
    
    if( !initialized ){
        errorLog << "saveSettingsToFile(string filename) - The HighPassFilter has not been initialized" << endl;
        return false;
    }
    
    std::fstream file; 
    file.open(filename.c_str(), std::ios::out);
    
    if( !saveSettingsToFile( file ) ){
        file.close();
        return false;
    }
    
    file.close();
    
    return true;
}

bool MovingAverageFilter::saveSettingsToFile(fstream &file){
    
    if( !file.is_open() ){
        errorLog << "saveSettingsToFile(fstream &file) - The file is not open!" << endl;
        return false;
    }
    
    file << "GRT_MOVING_AVERAGE_FILTER_FILE_V1.0" << endl;
    
    file << "NumInputDimensions: " << numInputDimensions << endl;
    file << "NumOutputDimensions: " << numOutputDimensions << endl;
    file << "FilterSize: " << filterSize << endl;
    
    return true;
}

bool MovingAverageFilter::loadSettingsFromFile(string filename){
    
    std::fstream file; 
    file.open(filename.c_str(), std::ios::in);
    
    if( !loadSettingsFromFile( file ) ){
        file.close();
        initialized = false;
        return false;
    }
    
    file.close();
    
    return true;
}

bool MovingAverageFilter::loadSettingsFromFile(fstream &file){
    
    if( !file.is_open() ){
        errorLog << "loadSettingsFromFile(fstream &file) - The file is not open!" << endl;
        return false;
    }
    
    string word;
    
    //Load the header
    file >> word;
    
    if( word != "GRT_MOVING_AVERAGE_FILTER_FILE_V1.0" ){
        errorLog << "loadSettingsFromFile(fstream &file) - Invalid file format!" << endl;
        return false;     
    }
    
    //Load the number of input dimensions
    file >> word;
    if( word != "NumInputDimensions:" ){
        errorLog << "loadSettingsFromFile(fstream &file) - Failed to read NumInputDimensions header!" << endl;
        return false;     
    }
    file >> numInputDimensions;
    
    //Load the number of output dimensions
    file >> word;
    if( word != "NumOutputDimensions:" ){
        errorLog << "loadSettingsFromFile(fstream &file) - Failed to read NumOutputDimensions header!" << endl;
        return false;     
    }
    file >> numOutputDimensions;
    
    //Load the filter factor
    file >> word;
    if( word != "FilterSize:" ){
        errorLog << "loadSettingsFromFile(fstream &file) - Failed to read FilterSize header!" << endl;
        return false;     
    }
    file >> filterSize;
    
    //Init the filter module to ensure everything is initialized correctly
    return init(filterSize,numInputDimensions);  
}

bool MovingAverageFilter::init(UINT filterSize,UINT numDimensions){
    
    //Cleanup the old memory
    initialized = false;
    inputSampleCounter = 0;
    
    if( filterSize == 0 ){
        errorLog << "init(UINT filterSize,UINT numDimensions) - Filter size can not be zero!" << endl;
        return false;
    }
    
    if( numDimensions == 0 ){
        errorLog << "init(UINT filterSize,UINT numDimensions) - The number of dimensions must be greater than zero!" << endl;
        return false;
    }
    
    //Resize the filter
    this->filterSize = filterSize;
    this->numInputDimensions = numDimensions;
    this->numOutputDimensions = numDimensions;
    processedData.clear();
    processedData.resize(numDimensions,0);
    initialized = dataBuffer.resize( filterSize, vector< double >(numInputDimensions,0) );
    
    if( !initialized ){
        errorLog << "init(UINT filterSize,UINT numDimensions) - Failed to resize dataBuffer!" << endl;
    }
    
    return initialized;
}

double MovingAverageFilter::filter(double x){
    
#ifdef GRT_SAFE_CHECKING
    //If the filter has not been initialised then return 0, otherwise filter x and return y
    if( !initialized ){
        errorLog << "filter(double x) - The filter has not been initialized!" << endl;
        return 0;
    }
#endif
    
    vector< double > y = filter(vector< double >(1,x));
    
    if( y.size() == 0 ) return 0;
    return y[0];
}
    
vector< double > MovingAverageFilter::filter(const vector< double > &x){
    
#ifdef GRT_SAFE_CHECKING
    //If the filter has not been initialised then return 0, otherwise filter x and return y
    if( !initialized ){
        errorLog << "filter(const vector< double > &x) - The filter has not been initialized!" << endl;
        return vector<double>();
    }
    
    if( x.size() != numInputDimensions ){
        errorLog << "filter(const vector< double > &x) - The size of the input vector (" << x.size() << ") does not match that of the number of dimensions of the filter (" << numInputDimensions << ")!" << endl;
        return vector<double>();
    }
#endif
    
    if( ++inputSampleCounter > filterSize ) inputSampleCounter = filterSize;
    
    //Add the new value to the buffer
    dataBuffer.push_back( x );
    
    for(unsigned int j=0; j<numInputDimensions; j++){
        processedData[j] = 0;
        for(unsigned int i=0; i<inputSampleCounter; i++) {
            processedData[j] += dataBuffer[i][j];
        }
        processedData[j] /= double(inputSampleCounter);
    }
    
    return processedData;
}

}//End of namespace GRT