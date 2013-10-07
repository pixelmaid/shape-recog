/**
 @file
 @author  Nicholas Gillian <ngillian@media.mit.edu>
 @version 1.0
 
 @section LICENSE
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
 
 @brief This class acts as a front end for the LIBSVM library (http://www.csie.ntu.edu.tw/~cjlin/libsvm/). 
 It implements a Support Vector Machine (SVM) classifier, a powerful classifier that works well on a wide
 range of classification problems, particularly on more complex problems that other classifiers (such as 
 the KNN, GMM or ANBC algorithms) might not be able to solve.
 
 @example ClassificationModulesExamples/SVMExample/SVMExample.cpp
 */

#ifndef GRT_SVM_HEADER
#define GRT_SVM_HEADER

#include "../../GestureRecognitionPipeline/Classifier.h"
#include "LIBSVM/libsvm.h"

namespace GRT {
    
using namespace LIBSVM;
    
#define SVM_MIN_SCALE_RANGE -1.0
#define SVM_MAX_SCALE_RANGE 1.0

class SVM : public Classifier{
public:
    /**
     Default constructor.
     
     Set the initial SVM settings, although these can be changed at any time using either init(...) function of the set... functions.
     
     @param UINT kernelType: this sets the SVM kernelType. Options are LINEAR_KERNEL, POLY_KERNEL, RBF_KERNEL, SIGMOID_KERNEL, PRECOMPUTED_KERNEL. The default kernelType is kernelType=LINEAR_KERNEL
     @param UINT svmType: this sets the SVM type. Options are C_SVC, NU_SVC, ONE_CLASS, EPSILON_SVR, NU_SVR. The default svmType is svmType=C_SVC
     @param bool useScaling: sets if the training/prediction data will be scaled to the default range of [-1. 1.]. The SVM algorithm commonly achieves a better classification result if scaling is turned on. The default useScaling value is useScaling=true
     @param bool useNullRejection: sets if a predicted class will be rejected if the classes' probability is below the classificationThreshold. The default value is useNullRejection=false
     @param bool useAutoGamma: sets if the SVM gamma parameter will automatically be computed, if set to true then gamma will be set to (1.0/numFeatures), where numFeatures is the number of features in the training data. The default value is useAutoGamma=true
     @param double gamma: sets the SVM gamma parameter. The default value is gamma=0.1
     @param UINT degree: sets the SVM degree parameter. The default value is degree=3
     @param double coef0: sets the SVM coef0 parameter. The default value is coef0=0
     @param double nu: sets the SVM nu parameter. The default value is nu=0.5
     @param double C: sets the SVM C parameter. The default value is C=1
     @param bool useCrossValidation: sets if the SVM model will be trained using cross validation. The default value is useCrossValidation=false
     @param UINT kFoldValue: sets the number of folds that will be used for cross validation. The default value is kFoldValue=10
     */
	SVM(UINT kernelType = LINEAR_KERNEL,UINT svmType = C_SVC,bool useScaling = true,bool useNullRejection = false,bool useAutoGamma = true,double gamma = 0.1,UINT degree = 3,double coef0 = 0,double nu = 0.5,double C = 1,bool useCrossValidation = false,UINT kFoldValue = 10);
    
    /**
     Default copy constructor.  Copies the settings from the rhs SVM instance to this instance
     
     @param const SVM &rhs: another instance of a SVM
     */
    SVM(const SVM &rhs);
    
    /**
     Default Destructor
     */
	virtual ~SVM();
    
    /**
     Defines how the data from the rhs SVM should be copied to this SVM
     
     @param const SVM &rhs: another instance of a SVM
     @return returns a pointer to this instance of the SVM
     */
    SVM &operator=(const SVM &rhs);
    
    /**
     This is required for the Gesture Recognition Pipeline for when the pipeline.setClassifier(...) method is called.  
     It clones the data from the Base Class Classifier pointer (which should be pointing to an SVM instance) into this instance
     
     @param Classifier *classifier: a pointer to the Classifier Base Class, this should be pointing to another SVM instance
     @return returns true if the clone was successfull, false otherwise
     */
    virtual bool clone(const Classifier *classifier);
    
    /**
     This trains the SVM model, using the labelled classification data.
     This overrides the train function in the Classifier base class.
     
     @param LabelledClassificationData &trainingData: a reference to the training data
     @return returns true if the SVM model was trained, false otherwise
     */
    virtual bool train(LabelledClassificationData &trainingData);
    
    /**
     This predicts the class of the inputVector.
     This overrides the predict function in the Classifier base class.
     
     @param VectorDouble inputVector: the input vector to classify
     @return returns true if the prediction was performed, false otherwise
     */
    virtual bool predict(VectorDouble inputVector);
    
    /**
     This saves the trained SVM model to a file.
     This overrides the saveModelToFile function in the Classifier base class.
     
     @param string filename: the name of the file to save the SVM model to
     @return returns true if the model was saved successfully, false otherwise
     */
    virtual bool saveModelToFile(string filename);
    
    /**
     This saves the trained SVM model to a file.
     This overrides the saveModelToFile function in the Classifier base class.
     
     @param fstream &file: a reference to the file the SVM model will be saved to
     @return returns true if the model was saved successfully, false otherwise
     */
    virtual bool saveModelToFile(fstream &file);
    
    /**
     This loads a trained SVM model from a file.
     This overrides the loadModelFromFile function in the Classifier base class.
     
     @param string filename: the name of the file to load the SVM model from
     @return returns true if the model was loaded successfully, false otherwise
     */
    virtual bool loadModelFromFile(string filename);
    
    /**
     This loads a trained SVM model from a file.
     This overrides the loadModelFromFile function in the Classifier base class.
     
     @param fstream &file: a reference to the file the SVM model will be loaded from
     @return returns true if the model was loaded successfully, false otherwise
     */
    virtual bool loadModelFromFile(fstream &file);
    
    
    /**
     This initializes the SVM settings and parameters.  Any previous model, settings, or problems will be cleared.
     
     @param UINT kernelType: this sets the SVM kernelType. Options are LINEAR_KERNEL, POLY_KERNEL, RBF_KERNEL, SIGMOID_KERNEL, PRECOMPUTED_KERNEL     @param UINT svmType: this sets the SVM type. Options are C_SVC, NU_SVC, ONE_CLASS, EPSILON_SVR, NU_SVR
     @param bool useScaling: sets if the training/prediction data will be scaled to the default range of [-1. 1.]. The SVM algorithm commonly achieves a better classification result if scaling is turned on
     @param bool useNullRejection: sets if a predicted class will be rejected if the classes' probability is below the classificationThreshold
     @param bool useAutoGamma: sets if the SVM gamma parameter will automatically be computed, if set to true then gamma will be set to (1.0/numFeatures), where numFeatures is the number of features in the training data
     @param double gamma: sets the SVM gamma parameter
     @param UINT degree: sets the SVM degree parameter
     @param double coef0: sets the SVM coef0 parameter
     @param double nu: sets the SVM nu parameter
     @param double C: sets the SVM C parameter
     @param bool useCrossValidation: sets if the SVM model will be trained using cross validation
     @param UINT kFoldValue: sets the number of folds that will be used for cross validation
     @return returns true if the SVM was initialized, false otherwise
     */
    bool init(UINT kernelType,UINT svmType,bool useScaling,bool useNullRejection,bool useAutoGamma,double gamma,UINT degree,double coef0,double nu,double C,bool useCrossValidation,UINT kFoldValue);
    
    /**
     Clears any previous model or problem.
     */
	void clear();
    
    /**
     This initializes the default SVM settings and parameters. Any previous model, settings, or problems will be cleared.
     */
	void initDefaultSVMSettings();

    /**
     Gets if cross validation is enabled.
     
     @return returns true if cross validation is enabled, false otherwise
     */
    bool getIsCrossValidationTrainingEnabled(){ return useCrossValidation; }
    
    /**
     Gets if the gamma parameter will be automatically computed from the training data. 
     If false, then the user needs to set the gamma parameter.
     
     @return returns true if the gamma parameter will be automatically computed, false otherwise
     */
    bool getIsAutoGammaEnabled(){ return useAutoGamma; }
    
    /**
     Gets the current SVM type as a string.
     
     If the type has not been set correctly then the string value UNKNOWN will be returned.
     
     @return returns the current SVM type as a string.
     */
	string getSVMType();
    
    /**
     Gets the current kernel type as a string.
     
     If the type has not been set correctly then the string value UNKNOWN will be returned.
     
     @return returns the current kernel type as a string.
     */
    string getKernelType();
    
    /**
     Gets the current degree value.
     
     @return returns the current degree value.
     */
    UINT getDegree() const;
    
    /**
     Returns the number of classes in the trained model.
     
     If the model has not been trained then 0 will be returned.
     
     @return returns the number of classes in the trained model or 0 if the model has not been trained
     */
    virtual UINT getNumClasses() const;
    
    /**
     Gets the current gamma value.
     
     @return returns the current gamma value.
     */ 
    double getGamma() const;
    
    /**
     Gets the current nu value.
     
     @return returns the current nu value.
     */
    double getNu() const;
    
    /**
     Gets the current coef0 value.
     
     @return returns the current coef0 value.
     */
    double getCoef0() const;
    
    /**
     Gets the current C value.
     
     @return returns the current C value.
     */
    double getC() const;
    
    /**
     Gets the last cross validation result, if the model has been trained and cross validation was enabled.
     
     @return returns the last cross validation result.
     */
    double getCrossValidationResult(){ return crossValidationResult; }
    
    /**
     Sets the SVM type.
     This should be one of the SVMTypes enumeration types.
     
     @param UINT svmType: the new SVM type, options are C_SVC, NU_SVC, ONE_CLASS, EPSILON_SVR, NU_SVR 
     @return returns true if the SVM type was set correctly, false otherwise
     */
    bool setSVMType(UINT svmType);
    
    /**
     Sets the kernel type.
     This should be one of the SVMKernelTypes enumeration types.
     
     @param UINT kernelType: the new kernel, options are LINEAR_KERNEL, POLY_KERNEL, RBF_KERNEL, SIGMOID_KERNEL, PRECOMPUTED_KERNEL 
     @return returns true if the kernel type was set correctly, false otherwise
     */
    bool setKernelType(UINT kernelType);
    
    /**
     Sets the SVM gamma parameter.  The user should only try and set this value manually if the useAutoGamma parameter has been set to false.
     
     @param double gamma: the new gamma value
     @return returns true if the gamma parameter was updated, false otherwise
     */
    bool setGamma(double gamma);
    
    /**
     Sets the SVM degree parameter.
     This is only used if the SVM kernel parameter is set to POLY_KERNEL.
     
     @param UINT degree: the new degree value
     @return returns true if the degree parameter was updated, false otherwise
     */
    bool setDegree(UINT degree);
    
    /**
     Sets the SVM nu parameter.
     This is only used if the SVM type parameter is set to NU_SVC, ONE_CLASS, or NU_SVR.
     
     @param double nu: the new nu value
     @return returns true if the nu parameter was updated, false otherwise
     */
    bool setNu(double nu);
    
    /**
     Sets the SVM coef0 parameter.  
     This is only used if the SVM kernel type parameter is set to POLY_KERNEL or SIGMOID_KERNEL.
     
     @param double coef0: the new coef0 value
     @return returns true if the gamcoef0ma parameter was updated, false otherwise
     */
    bool setCoef0(double coef0);
    
    /**
     Sets the SVM C parameter.  
     This is only used if the SVM type parameter is set to C_SVC, EPSILON_SVR or NU_SVR.
     
     @param double C: the new C value
     @return returns true if the C parameter was updated, false otherwise
     */
    bool setC(double C);
    
    /**
     Sets the kFold cross validation value.
     
     @param UINT kFoldValue: the new kFoldValue, must be greater than 0
     return returns true if the kFoldValue was set, false otherwise
     */
    bool setKFoldCrossValidationValue(UINT kFoldValue);
    
    /**
     Sets if the gamma parameter will be automatically computed from the training data.
     
     @param bool useAutoGamma: the new useAutoGamma setting
     return returns true if the useAutoGamma was set, false otherwise
     */
    bool enableAutoGamma(bool useAutoGamma);
    
    /**
     Sets if cross validation should be used during the training phase.
     
     @param bool useCrossValidation: the new useCrossValidation setting
     return returns true if the useCrossValidation was set, false otherwise
     */
    bool enableCrossValidationTraining(bool useCrossValidation);

protected:
    void deleteProblemSet();
    bool validateProblemAndParameters();
    bool validateSVMType(UINT svmType);
    bool validateKernelType(UINT kernelType);
    bool convertLabelledClassificationDataToLIBSVMFormat(LabelledClassificationData &trainingData);
	bool trainSVM();
    
	bool predict_(VectorDouble &inputVector);
	bool predict_(VectorDouble &inputVector,double &maxProbability, vector<double> &probabilites);
    
	bool problemSet;
	struct svm_model *model;
	struct svm_parameter param;
	struct svm_problem prob;
	UINT kFoldValue;
	double classificationThreshold;
	double crossValidationResult;
	bool useAutoGamma;
    bool useCrossValidation;
    
    static RegisterClassifierModule< SVM > registerModule;
    
public:
    
    enum SVMTypes{ C_SVC = 0, NU_SVC, ONE_CLASS, EPSILON_SVR, NU_SVR };
    enum SVMKernelTypes{ LINEAR_KERNEL = 0, POLY_KERNEL, RBF_KERNEL, SIGMOID_KERNEL, PRECOMPUTED_KERNEL };

};
    
} //End of namespace GRT

#endif //GRT_SVM_HEADER

