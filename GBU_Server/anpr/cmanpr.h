
/*******************************************************************************
 * CMANPR header file - 7.2.6
 *
 * 2005-2012 (c) ARH Inc. (http://www.arhungary.hu)
 ******************************************************************************/

/** \file cmanpr.h
 * \brief CMANPR header file
 *
 * Automatic Number Plate Reader engine.
 *
 * \author ARH Inc. (http://www.arhungary.hu)
 * \version 7.2.6
 * \date 2005-2012
 *
 * \mainpage CMANPR
 * \section cmanpr_sdk The Carmen Automatic Number Plate Reader SDK
 * The CARMEN ANPR is an intelligent image processing engine based on the number plate reading software of the ARH Inc. 
 * As a result of continuous development since 1997, the seventh generation of the software provides numerous options. 
 * Besides recognizing characters of a number plate, the engine is also capable of identifying additional attributes such as: 
 * 
 *  - number plate type (within a country/state)
 *  - plate color (background color)
 *  - coordinates of the plate and its characters
 *  - confidence level value.  
 *
 * The engine can be configured by its parameters located in the gxsd.dat file. By setting these properties appropriately 
 * (according to the environment of the camera) the speed of the recognition process can be increased.
 * 
 * \section cmanpr_properties Properties of the CMANPR module
 *
 * \subsection cmanpr_property_anprname anprname - Name of the actual engine
 *
 * The name of the actual (current) engine. It can be altered during runtime. Its value can be set according
 * to the following: <b>engine module name : property group</b>
 * If there is no specified property group then the cmanpr module handles it as 'default'.
 * <b>NOTE</b>: In case of SaveProperties, the module is not capable of saving the property value to the gxsd.dat file.
 *
 * Default value: not available
 *
 * \section engine_properties Properties of the engines
 *
 * The property name of the module is \a cmanpr in the property tree.
 * \verbatim
   <default>
      <cmanpr>
         <datafile value="cmanpr-7.0.6.31.dat"/>
         <size value="20"/>
		 ...
   \endverbatim
 *
 * \subsection cmanpr_property_datafile datafile - Name of data file of the engine
 *
 * This file has to be in the module folder. The name of the default data file is
 * {engine name}.dat (i.e. cmanpr-7.82-latin.dat for the cmanpr-7.82-latin engine).
 * In case of having a data file with parameters optimized for some special
 * number plate types (for example cmanpr-7.82-latin.dat for European plates)
 * this file can be used as well.
 *
 * Default value: {module name}.dat
 *
 *
 * \subsection cmanpr_property_contrast_min contrast_min - Minimal contrast
 *
 * The supposed minimal difference between the grayscale value of the
 * number plate characters and the plate background.
 *
 * Engine dependent default value.
 *
 *
 * \subsection cmanpr_property_size size - Average height of the characters
 *
 * The average height of the number plate characters in the image in pixels.
 *
 * <b>NOTE</b>: size_min \&lt;= size \&lt;= size_max
 * So, the size value has to be equal to or greater than size_min and equal to
 * or less than size_max otherwise the engine may return no data.
 *
 * Engine dependent default value.
 *
 *
 * \subsection cmanpr_property_size_min size_min - Minimum height of the characters
 *
 * The minimum height of the number plate characters in the image in pixels.
 *
 * Engine dependent default value.
 *
 *
 * \subsection cmanpr_property_size_max size_max - Maximum height of characters
 *
 * The maximum height of the number plate characters in the image in pixels.
 *
 * Engine dependent default value.
 *
 *
 * \subsection cmanpr_property_nchar_min nchar_min - Minimum number of the characters in the plate
 *
 * The minimum number of the number plate characters in the plate. The engine doesn't return number plates
 * on which the number of characters is less than the nchar_min value.
 *
 * <b>NOTE</b>: This property is ignored if the plate type recognition is enabled!
 *
 * Engine dependent default value.
 *
 *
 * \subsection cmanpr_property_nchar_max nchar_max - Maximum number of characters int the plate
 *
 * The maximum number of the number plate characters in the plate. The engine doesn't return number plates
 * on which the number of characters is more than the nchar_max value.
 *
 * <b>NOTE</b>: This property is ignored if the plate type recognition is enabled!
 *
 * Engine dependent default value.
 *
 *
 * \subsection cmanpr_property_slope slope - Average slope of the number plate
 *
 * The average slope of the number plate in the image. This value is represented in percent (%) and
 * it is positive if the horizontal axis of the number plate slopes downwards viewing from left to right.
 *
 * <b>NOTE</b>: slope_min \&lt;= slope \&lt;= slope_max
 * So, the slope value has to be equal to or greater than slope_min and equal to
 * or less than slope_max otherwise the engine may return no data.
 *
 * Engine dependent default value.
 *
 *
 * \subsection cmanpr_property_slope_min slope_min - Minimum slope of the number plate
 *
 * The minimum slope of the number plate in the image. This value is represented in percent (%) and
 * it is positive if the horizontal axis of the number plate slopes downwards viewing from left to right.
 *
 * Engine dependent default value.
 *
 *
 * \subsection cmanpr_property_slope_max slope_max - Maximum slope of the number plate
 *
 * The maximum slope of the number plate in the image. This value is represented in percent (%) and
 * it is positive if the horizontal axis of the number plate slopes downwards viewing from left to right.
 *
 * Engine dependent default value.
 *
 *
 * \subsection cmanpr_property_slant slant - Average slant of the number plate
 *
 * The average slant of the number plate characters in the image. This value is represented
 * in percent (%) and it is positive if the vertical axis of the characters slants
 * to the left viewing from bottom to top.
 *
 * <b>NOTE</b>: slant_min \&lt;= slant \&lt;= slant_max
 * So, the slant value has to be equal to or greater than slant_min and equal to or less than
 * slant_max otherwise the engine may return no data.
 *
 * Engine dependent default value.
 *
 *
 * \subsection cmanpr_property_slant_min slant_min - Minimum slant of the number plate
 *
 * The minimum slant of the number plate characters in the image. This value is represented
 * in percent (%) and it is positive if the vertical axis of the characters slants to the
 * left viewing from bottom to top.
 *
 * Engine dependent default value.
 *
 *
 * \subsection cmanpr_property_slant_max slant_max - Maximum slant of the number plate
 *
 * The maximum slant of the number plate characters in the image. This value is represented
 * in percent (%) and it is positive if the vertical axis of the characters slants to the left
 * viewing from bottom to top.
 *
 * Engine dependent default value.
 *
 *
 * \subsection cmanpr_property_unicode_in_text unicode_in_text - Representation of the non ASCII characters in the text parameter of the cmNP structure
 *
 * Possible values are:
 *
 *  - 0 : The non ASCII characters are substituted by an exclamation mark ('!')
 *  - 1 : Each non ASCII character is represented with 6 ASCII characters: '(xxxx)', where
 *		xxxx is the Unicode code of the character in hexadecimal form including the leading zeroes
 *
 *  Default value: 1
 *
 *
 * \subsection cmanpr_property_timeout timeout - Time limit
 *
 * The length of the time interval in milliseconds in which the
 * module tries to find new number plates. The interval starts when
 * cm_findfirst() is called. At the end of this period the engine tries to
 * finish searching new plates and any additional call of cm_findnext()
 * will result no plates found. Zero timeout value means no time limit.
 *
 * Default value: 1000
 * By setting the timeout value before the cm_findnext () call, the timing will be restarted and
 * the evaluation lasts till the newly specified time interval.
 *
 * Example:
 * If the value of the timeout is set to 500
 * The cm_findfirst() returns successfully after 200 ms. In this case after additional cm_findnext()
 * call 300 ms would be available. However, if the timeout is set to 500 after cm_findfirst(),
 * then 500ms would be available for further cm_findnext() calls.
 *
 * \subsection cmanpr_property_xtoyres xtoyres - The ratio of horizontal and vertical resolutions
 *
 * The ratio of the horizontal and vertical resolutions of the plate. This value is represented in percent (%).
 * The horizontal resolution is the ratio of the width of the plate in the image and the real width of the plate.
 * The vertical resolution is the ratio of the height of the plate in the image and the real height of the plate.
 * Zero value to xtoyres means automatic setting of the ratio by cm_findfirst() using xsize and ysize parameters of
 * the image as follows: if xsize/ysize is less or equal to 7/3, xtoyres is set to 100, if xsize/ysize is greater than 7/3, xtoyres is set to 200.

 * The ratio of the horizontal and vertical resolutions of the plate. This value is represented in percent (%).
 * The horizontal resolution is the ratio of the width of the plate in the image and the real width of the plate,
 * the vertical resolution is the ratio of the height of the plate in the image and the real height of the plate.
 *
 * Engine dependent default value.
 *
 * This parameter can be set manually using images that contain plates of the same type.
 * Calculating the average of the ratio r of the width and the height of the plates
 * on images and by calculating the R ratio of the width and the height of a real plate: (1) xtoyres=[(100*r)/R+0,5].
 *
 *
 * \subsection cmanpr_property_colortype colortype - Background color of the plate
 *
 * The type of the plates to be read by the module.
 *
 * Possible values are:
 *  - 0 : Module searches for all kinds of plates in the image.
 *  - 1 : Module searches for plates only with black characters on white background.
 *  - 2 : Module searches for plates only with white characters on black background.
 *
 * Default value: 0
 *
 *
 * \subsection cmanpr_property_gaptospace gaptospace - Gaps between characters
 *
 * If this parameter is set to a nonzero value, the module searches for gaps between characters that can be spaces.
 * Space characters are inserted into these positions in the text and wtext fields of the result structure.
 * If the value is zero, no spaces will appear in the result.
 *
 * Default value: 0
 *
 *
 * \subsection cmanpr_property_general general - Selecting general or special returning mode
 *
 * <b>NOTE</b>: Values 4, 5 and 6 can be applied only if the .dat file contains ADR information 
 * (e.g. cmanpr-7.74-latin-ADR.dat. For more information feel free to contact support@arhungary.hu). 
 * Other engines use only two values: 0 and 1.
 *
 * By this property, the reading modes can be selected.
 *
 * Different functions can be activated by switching certain bits:
 *  - 1. bit: searching for any kind of license plate (does not search for ADR plates)
 *  - 2. bit: turning off returning the value of the license plate with plate type (the main purpose of it to make 
 * the returning of the license plate possible to turn off in case of reading the ADR plate)
 *  - 3. bit: searching for ADR plates with text
 *  - 4. bit: searching for empty ADR plates detection of empty ADR plates in the image (EADR)
 *
 * The engine contains the algorithm from the version 7.2.7.111, however, a data file &mdash; that contains the information 
 * necessary for the EADR &mdash; is required for its usage. The EADR can be called by the cm_findemptyadr() property only right 
 * after the cm_findfirst() property, otherwise it returns with &apos;No image&apos; error message. If the engine finds a plate like that, 
 * it will upload the data of the frame and the confidence to the cmNP structure, the type will be 9799.
 * The EADR function can be turned on by the 4th bit of the parameter.
 * 
 * For example: the algorithm can return license, ADR and EADR plate in case of the general=13 value (if the .dat is correct).
 * 
 * Possible values:
 *	- 0 : special mode, license plate text results returned only if the plate type is also recognized <b>[0000]</b>
 *	- 1 : general mode, text results are always returned (<b>NOTE</b>: ADR results are not returned) <b>[0001]</b>
 *	- 4 : returns ADR and license plate texts only with recognized plate types  <b>[0100]</b>
 *	- 5 : every result is returned <b>[0101]</b>
 *	- 6 : only ADR types with plate type recognition are returned <b>[0110]</b>
 *	- 8 : only EADR and license plate with plate type recognition <b>[1000]</b>
 *	- 9 : 9: only EADR and license plate <b>[1001]</b>
 *	- 10 : only EADR <b>[1010]</b>
 *	- 12 : license plate with plate type, ADR and EADR <b>[1100]</b>
 *	- 13 : every result is returned <b>[1101]</b>
 *	- 14 : only ADR and EADR <b>[1110]</b>
 *
 * Default value: 1
 *
 *
 * \subsection cmanpr_property_depth depth - Heuristic sensitivity
 *
 * CMANPR engines with license plate type recognition use more sophisticated algorithms
 * than former ones, thus not only the plate types are recognized but text accuracy is also improved
 * in most cases. If the recognition time is too long for the application, the depth of search may
 * be lowered through this parameter, however the accuracy of both text and plate type reading
 * will be affected. If the application is not time-crucial, then this depth may be increased to get
 * higher recognition accuracy. If set to 0, plate type recognition and heuristics are disabled.
 *
 * <b>NOTE</b>: For reading plate colors, plate type recognition has to be enabled!
 *
 * Engine dependent default value. Possible values: 0-500.
 *
 *
 * \subsection cmanpr_property_adapt_environment adapt_environment - Accelerated mode selector
 *
 * This property serves as an accelerator for the recognition process; it can be applied only
 * when license plate type recognition is enabled.
 *
 * Possible values: 0 or 1
 *
 * Standard mode if set to 0.
 *
 * If set to 1, CMANPR engine applies real-time adaptation methods based on statistical measurements.
 * In many cases reading a few recognized license plates is enough to adapt to the environment and get
 * even two times faster license plate recognition, however recognition time and accuracy is optimized
 * only when the application is running.
 *
 * <b>IMPORTANT NOTES</b> when using adapt_environment:
 * 	- \b Timeout
 * 		Acceleration is VERY high using engines with large plate type set, if only a few different plate
 * 		types are common at the recognition location (e.g. Arabic engine used in Bahrain). Although the
 * 		common types will have intensively accelerated recognition, the uncommon ones will have about
 * 		the same recognition time as without using this option. Because of this, using low timeout value
 * 		(e.g. based on the mean recognition time calculated using acceleration) may end up in loosing all
 * 		the uncommon license plates. The timeout value must be set properly, not too low, taking in
 * 		consideration all aspects.
 *
 * 	- \b Recognition \b accuracy
 * 		Acceleration is a very useful option in many cases (especially in time-crucial applications), but
 * 		it can easily cause some hard-to-understand "errors", e.g. the same license plate on the same picture
 * 		may be read at first but misread or not read at all after some other plates. This is because of statistical
 * 		reasons and it is not very common, however it may happen especially when using low timeout values
 * 		(read note no. 1). According to our tests text reading accuracy is nearly the same with or without
 * 		acceleration. Plate type recognition accuracy is more sensitive to this option, but this also means
 * 		that they might even be improved in some cases.
 *
 * 	- \b Error \b reporting
 * 		Using acceleration makes it difficult to reproduce errors or misreadings, because the engine continuously
 * 		changes recognition parameters. Thus before reporting an error please check it also with acceleration
 * 		disabled to help us decide whether it is an acceleration-related issue.
 *
 * Default value: 0
 *
 *
 * \subsection cmanpr_property_analyzecolors analyzecolors - Color recognition mode
 *
 * This property selects the mode of color recognition.
 *
 * Possible values:
 *	- 0 : Color identification is disabled
 *	- 1 : CMANPR engine returns discrete color values (exact values are read and
 *		the statistically most possible results are given)<BR>
 *		<b>NOTE</b>: Discrete results may be incorrect - because of statistical reasons - in
 *				case of plates with formerly unseen colors (e.g. blue plates will not be
 *				identified if there were only red and orange ones available when the CMANPR
 *				data file was created)
 *	- 2 : CMANPR engine returns the exact RGB values read (further processing required)
 *
 * The CMANPR engine is able to recognize the color of the license plate only when the
 * following requirements are fulfilled:
 *		- the license plate type recognition has to be enabled (\c depth > 0)
 *		- the license plate type must be identified by the engine (if not, the identified
 *		  color value might be wrong)
 *		- the \c analyzecolors property has to be set to 1 or 2
 *
 * Default value: 0
 *
 *
 * \subsection cmanpr_property_whitebalance whitebalance - White balance correction
 *
 * When applying color recognition, the white balance is set automatically by the engine.
 * In some special cases (e.g. special camera settings, extreme whether or light conditions)
 * the returned colors may not be correct. To avoid misrecognition of colors the whitebalance
 * property can be used.
 *	- If it is set to 0 then white balance correction is not used.
 *	- If it is set to 100 then maximal white balance correction is applied
 *
 * 24/7 use of white balance correction can also be applied. Incorrect results may return only
 * when the camera is used in very different environmental conditions in a very short time
 * (e.g. the camera is used at night with whitebalance 100, turned off and then turned on in
 * the morning with the same settings).
 *
 * Default value: 100
 *
*/

#ifndef CMANPR_H_INCLUDED
#define CMANPR_H_INCLUDED
//-----------------------------------------------------------------------------
#include "gxerror.h"
#include "gxsd.h"
#include "gximage.h"
#include "gxtypes.h"

#ifdef GX_NAMESPACES
	using namespace gx;
	namespace cm {
#endif

#ifdef GX_DOTNET
	#pragma unmanaged
#endif

/******************************************************************************/
/** Group codes */
/******************************************************************************/
enum CMANPR_CALL_GROUP_CODES {
	GX_CALL_GROUP_CMANPR		=	0x20000000	/**< Group code of the CMANPR module. */
};

#if !defined(GX_SWIGIF)

/******************************************************************************/
/** Call codes for the ANPR operations */
/******************************************************************************/
enum CMANPR_CALL_CODES {
	CM_CALL_FINDFIRST	= GX_CALL_GROUP_CMANPR,		/**< Call code for the cm_findfirst() function. */
	CM_CALL_FINDNEXT	= GX_CALL_GROUP_CMANPR + 1,	/**< Call code for the cm_findnext() function. */
	CM_CALL_FORMAT		= GX_CALL_GROUP_CMANPR + 2,	/**< Call code for the cm_format() function. */
	CM_CALL_FINDENGINES	= GX_CALL_GROUP_CMANPR + 3,	/**< Call code for the cm_findengines() function (Unicode version). */
	CM_CALL_FINDENGINESA= GX_CALL_GROUP_CMANPR + 4,	/**< Call code for the cm_findengines() function (ASCII version). */
	CM_CALL_FINDEMPTYADR= GX_CALL_GROUP_CMANPR + 14,

	CM_CALL_GETENGINEPROPERTIES= GX_CALL_GROUP_CMANPR + 0xf0, /**< Call code for the cm_getengineproperties() function (Unicode version). */
	CM_CALL_LRTEXT2DISPLAY= GX_CALL_GROUP_CMANPR + 0xf1, /**< Call code for the cm_lrtext2display() function (Unicode version). */
};
#endif

#ifdef GX_DOTNET
	#pragma managed
#endif

/******************************************************************************/
/** CMANPR error codes */
/******************************************************************************/
GX_ENUM CMANPR_ERROR_CODES {
	GX_EINVALIDENGINE		=	GX_CALL_GROUP_CMANPR | 0x2060,	/**< Invalid engine */
	CME_DATAFILE_NOT_FOUND	=	GX_CALL_GROUP_CMANPR | 0x3000,	/**< No data file found */
	CME_DATAFILE_CORRUPTED	=	GX_CALL_GROUP_CMANPR | 0x3001,	/**< Invalid data file */
	CME_NO_IMAGE			=	GX_CALL_GROUP_CMANPR | 0x3002,	/**< No image to give for the engine */
	CME_UNKNOWN_PROPERTY	= 	GX_CALL_GROUP_CMANPR | 0x3003,	/**< Invalid engine property */
	CME_HWKEY_OPEN			=	GX_CALL_GROUP_CMANPR | 0x3004,	/**< Hardware key opening error */
	CME_HWKEY_LOCK			=	GX_CALL_GROUP_CMANPR | 0x3005,	/**< Hardware key locking error */
	CME_HWKEY_IO			=	GX_CALL_GROUP_CMANPR | 0x3006,	/**< Hardware key input-output error */
	CME_ENGINE				=	GX_CALL_GROUP_CMANPR | 0x3007,	/**< Internal engine error */
	CME_BUFFERFULL			=	GX_CALL_GROUP_CMANPR | 0x3008,	/**< Buffer full */
	CME_INVAL				=	GX_CALL_GROUP_CMANPR | 0x3009,	/**< Invalid parameter*/
	CME_NOMEM				=	GX_CALL_GROUP_CMANPR | 0x300a,	/**< Memory allocation error*/
	CME_INVIMG				=	GX_CALL_GROUP_CMANPR | 0x300b,	/**< Invalid image*/
	CME_GXSD				=	GX_CALL_GROUP_CMANPR | 0x300c,	/**< GXSD service not installed properly*/
	CME_UNHANDLED			=	GX_CALL_GROUP_CMANPR | 0x300f,	/**< Unhandled cmanpr exception*/
};

/*******************************************************************************
 * General structures
 ******************************************************************************/

#ifdef GX_DOTNET
	#pragma unmanaged
#endif

#if !defined(GX_SWIGIF) /*(*/

#ifndef GX_DOTNET /*(*/

#ifndef __cplusplus
/** Structure for a character (ANSI C only). */
struct cmNP_CHR {
	struct gxPG4	frame;		/**< Coordinates of the character tip frame. */
	int 			bkcolor;	/**< Background color of the character tip. The color is in BGR format. */
	int 			color;		/**< Color of the character tip. The color is in BGR format. */
	int				code;		/**< Unicode code of the character. */
	int				confidence; /**< The confidence level of the character tip. */
};
#endif

/** Structure for the number plate. */
struct cmNP {

	int				gxid;		/**< Identifier of the cmNP structure. */
 	struct gxPG4	frame;		/**< The coordinates of the license plate frame. */
	int 			bkcolor;	/**< Background color of the license plate. The color is in BGR format. */
	int 			color;		/**< Color of the license plate text. The color is in BGR format. */
	int				type;		/**< Type of the license plate. */
	int				confidence;	/**< Confidence level of the license plate. */

#ifdef __cplusplus

	/** Structure for a character. */
	struct CHR {
		gxPG4		frame;		/**< Coordinates of the character tip frame. */
		int 		bkcolor;	/**< Background color of the character tip. The color is in BGR format. */
		int 		color;		/**< Color of the character tip. The color is in BGR format. */
		int			code;		/**< Unicode code of the character. */
		int			confidence; /**< The confidence level of the character tip. */
	};

	int				ntip;		/**< Number of the all character tips. */
	CHR*			tips;		/**< Pointer to the all character tips. */
	int				ncharacter;	/**< Number of the character tips of the plate text. */
	CHR**			characters;	/**< Pointer to the character tips of the plate text. */

#else

	int					ntip;		/**< Number of the all character tips. */
	struct cmNP_CHR*	tips;		/**< Pointer to the all character tips. */
	int					ncharacter;	/**< Number of the character tips of the plate text. */
	struct cmNP_CHR**	characters;	/**< Pointer to the character tips of the plate text. */

#endif

	char*			text;		/**< Pointer to the plate text in ASCII string format. */
	wchar_t*		wtext;		/**< Pointer to the plate text in Unicode string format. */

};



#else

/** Structure for the number plate. */
struct cmNP {
	int			gxid;			/**< Identifier of the cmNP structure. */
 	_gxPG4		frame;			/**< The coordinates of the license plate frame. */
	int 		bkcolor;		/**< Background color of the license plate. The color is in BGR format. */
	int 		color;			/**< Color of the license plate text. The color is in BGR format. */
	int			type;			/**< Type of the license plate. */
	int			confidence;		/**< Confidence level of the license plate. */

	/** Structure for a character tip */
	struct CHR {
		_gxPG4		frame;		/**< Coordinates of the character tip frame. */
		int 		bkcolor;	/**< Background color of the character tip. The color is in BGR format. */
		int 		color;		/**< Color of the character tip. The color is in BGR format. */
 		int			code;		/**< Unicode code of the character. */
		int			confidence; /**< The confidence level of the character tip. */
	};

	int				ntip;		/**< Number of the all character tips. */
	CHR*			tips;		/**< Pointer to the all character tips. */
	int				ncharacter;	/**< Number of the character tips of the plate text. */
	CHR**			characters;	/**< Pointer to the character tips of the plate text. */
	char*			text;		/**< Pointer to the plate text in ASCII string format. */
	wchar_t*		wtext;		/**< Pointer to the plate text in Unicode string format. */
};


#endif /* GX_DOTNET )*/

/*******************************************************************************
 * Structures for ANPR functions
 ******************************************************************************/

/** Parameter structure for cm_findfirst() function. */
struct CM_FINDFIRST {
	const struct gxIMAGE*	pimage;			/**< Pointer to an initialized image structure. */
	struct cmNP**			panprresult;	/**< Pointer to a pointer where the function reallocates the result. */
};

/** Parameter structure for cm_findnext() function. */
struct CM_FINDNEXT {
	struct cmNP**			panprresult;	/**< Pointer to a pointer where the function reallocates the result. */
};

/** Parameter structure for cm_findemptyadr() function. */
struct CM_FINDEMPTYADR{
	struct cmNP**			padrresult;		/**< Pointer to a pointer where the function reallocates the result. */
};

/** Parameter structure for the cm_getengineproperties() function (Unicode version). */
struct CM_PARM_GETENGINEPROPERTIES
{
	wchar_t			*proplist;		/**< Pointer to a memory area where to store the names. */
	int				sproplist;		/**< Size of the memory area in characters (not in bytes). */
	const wchar_t	*separator;		/**< Separator string to separate the properties. */
	bool			b_value;		/**< The function returns the property names with or without the values of the properties. */
};

/** Parameter structure for the cm_lrtext2display() function (Unicode version). */
struct CM_PARM_LRTEXT2DISPLAY
{
	wchar_t			*disptext;		/**< Pointer to a memory area where to store the displayable lrtext. */
	int				sdisptext;		/**< Size of the memory area in characters (not in bytes). */
	const wchar_t	*lrtext;		/**< Text read from left to right. */
};

/** Parameter structure for cm_format() function. */
#ifdef __cplusplus

struct CM_FORMAT {
	const gxIMAGE*		pimage;		/**< Pointer to a source image. */
	int					ntip;		/**< It will contain the number of tips. */
	const cmNP::CHR*	tips;		/**< Buffer for the result tips. */
	cmNP**				panprresult;/**< Pointer to a pointer where the function reallocates the result. */
};

#else

struct CM_FORMAT {
	const struct gxIMAGE*		pimage;		/**< Pointer to a source image. */
	int							ntip;		/**< It will contain the number of tips. */
	const struct cmNP_CHR*		tips;		/**< Buffer for the result tips. */
	struct cmNP**				panprresult;/**< Pointer to a pointer where the function reallocates the result. */
};
#endif


//#ifdef WIN32 /*(*/

/** CMANPR defined values. */
enum {
	SENGNAME = 128	/**< Maximal length of the engine name. */
};

typedef	wchar_t	ENGNAME[SENGNAME+1];		/**< Type of the engine name for unicode format. */
typedef	char	ENGNAMEA[SENGNAME+1];		/**< Type of the engine name for ASCII format. */

/** Parameter structure for cm_findengines() function. */
struct CM_FINDENGINES {
	ENGNAME**					engines;	/**< Pointer to a buffer to store the name of the engines. The function reallocates the buffer for the names. */
	int*						nengine;	/**< The number of the found engines */
};

/** Parameter structure for cm_findenginesa() function. */
struct CM_FINDENGINESA {
	ENGNAMEA**					engines;	/**< Pointer to a buffer to store the name of the engines. The function reallocates the buffer for the names. */
	int*						nengine;	/**< The number of the found engines */
};

//#endif	/* WIN32 )*/

#endif	/* !GX_SWIGIF )*/

/*******************************************************************************
 * Inline functions
 *******************************************************************************/
#if !defined(NO_GX_FUNCTIONS) && !defined(GX_SWIGIF) /*(*/

/******************************************************************************/
/** Reads the first number plate from the image.
 *
 * By calling the cm_findfirst() function the application can read a number plate
 * from an image. The function returns the character tips of the number plate,
 * and the text of the plate in ASCII and Unicode string format.
 *
 * \param handle		The gxHANDLE value retrieved by the gx_openmodule() function
 *						of the gxsd module.
 * \param pimage		Points to the gxIMAGE structure which contains the image to be
 *						scanned for number plates.
 * \param panprresult	Points to the cmNP* pointer which receives the data of the
 *						number plate found. The pointer value (*pranprresult) is
 *						allowed to be NULL or a cmNP* pointer retrieved by a previous
 *						call of the cm_findfirst(), cm_findnext() or cm_format()
 *						functions.\n
 *						In both cases the CMANPR module allocates new
 *						memory space for the result if necessary. The application
 *						must free this pointer. If the function returns NULL for
 *						the *panprresult pointer it means that no plate was found.
 * \return	On error false is returned and the error code/string in the GX system
 *			is set appropriately. ( see gx_geterror() ) */
inline int cm_findfirst(struct gxHANDLE handle, const struct gxIMAGE* pimage,
							struct cmNP** panprresult) {
	struct CM_FINDFIRST find;
	find.pimage = pimage;
	find.panprresult = panprresult;
	return gx_call(handle, CM_CALL_FINDFIRST, &find);
}

/******************************************************************************/
/** Reads the next number plate from the image.
 *
 * By calling the cm_findnext() function the application can read additional
 * number plates from an image. An error occurs if an application calls the
 * cm_findnext() function before it calls the cm_findfirst() function. The function
 * returns the character tips of the number plate, and the text of the plate in
 * ASCII and Unicode string format.
 *
 * \param handle	The gxHANDLE value retrieved by the gx_openmodule() function of the
 *					gxsd module.
 * \param panprresult	Points to the cmNP* pointer which receives the data of the
 *						number plate found. The pointer value (*pranprresult) is
 *						allowed to be NULL or a cmNP* pointer retrieved by a previous
 *						call of the cm_findfirst(), cm_findnext() or cm_format()
 *						functions.\n
 *						In both cases the CMANPR module allocates new
 *						memory space for the result if necessary. The application
 *						must free this pointer. If the function returns NULL for
 *						the *panprresult pointer it means that no plate was found.
 * \return	On error false is returned and the error code/string in the GX system
 *			is set appropriately. ( see gx_geterror() ) */
inline int cm_findnext(struct gxHANDLE handle, struct cmNP** panprresult) {
	struct CM_FINDNEXT find;
	find.panprresult = panprresult;
	return gx_call(handle, CM_CALL_FINDNEXT, &find);
}
/******************************************************************************/
/** Reads the empty ADR plate from the image.
 *
 * An error occurs if an application calls the cm_findemptyadr() function 
 * before it calls the cm_findfirst() function.
 * 
 * \param handle		The gxHANDLE value retrieved by the gx_openmodule() function
 *						of the gxsd module.
 * \param padrresult	Points to the cmNP* pointer which receives the data of the
 *						ADR plate. The pointer value (*pranprresult) is
 *						allowed to be NULL. If the function returns NULL for
 *						the *panprresult pointer it means that no adr plate was found.
 * \return	On error false is returned and the error code/string in the GX system
 *			is set appropriately. ( see gx_geterror() ) */
inline int cm_findemptyadr(struct gxHANDLE handle, struct cmNP** padrresult) {
	struct CM_FINDEMPTYADR find;
	find.padrresult = padrresult;
	return gx_call(handle, CM_CALL_FINDEMPTYADR, &find);
}
/******************************************************************************/
/** Formats the number plate result from character tips.
 *
 * By calling the cm_format() function the application can create a number plate
 * result from character tips. The application needs to call this function to
 * retrieve the correct plate text if the number plate tips are changed. (for
 * example: the program combines two or more number plate results)
 *
 * \param handle		The gxHANDLE value retrieved by the gx_openmodule() function
 *						of the gxsd module.
 * \param pimage		Points  to the gxIMAGE structure which contains the image to be
 *						scanned for number plates.
 * \param ntip			Number of the character tips.
 * \param tips			Points  to the character tips.
 * \param panprresult	Points to the cmNP* pointer which receives the data of the
 *						number plate found. The pointer value (*pranprresult) is
 *						allowed to be NULL or a cmNP* pointer retrieved by a previous
 *						call of the cm_findfirst(), cm_findnext() or cm_format()
 *						functions.\n
 *						In both cases the CMANPR module allocates new
 *						memory space for the result if necessary. The application
 *						must free this pointer. If the function returns NULL for
 *						the *panprresult pointer it means that no plate was found.
 * \return	On error false is returned and the error code/string in the GX system
 *			is set appropriately. ( see gx_geterror() ) */
#ifdef __cplusplus
inline int cm_format(struct gxHANDLE handle, const struct gxIMAGE* pimage, int ntip,
						const struct cmNP::CHR* tips, struct cmNP** panprresult) {
#else
inline int cm_format(struct gxHANDLE handle, const struct gxIMAGE* pimage, int ntip,
						const struct cmNP_CHR* tips, struct cmNP** panprresult) {
#endif
	struct CM_FORMAT fmt;
	fmt.pimage = pimage;
	fmt.ntip = ntip;
	fmt.tips = tips;
	fmt.panprresult = panprresult;
	return gx_call(handle, CM_CALL_FORMAT, &fmt);
}


//#ifdef WIN32  /*(*/
/******************************************************************************/
/** Find the installed engines in the system (Unicode version).
 *
 * By calling the cm_findengines() function the application can find the engines
 * in the GX system.
 *
 * \param handle	The gxHANDLE value retrieved by the gx_openmodule() function of the
 *					gxsd module.
 * \param pengines	Pointer to a buffer to store the name of the engines. The function
 *					reallocates the buffer for the names. To free the buffer use
 *					the gx_globalfree() function.
 * \param nengine	The number of the found engines.
 * \return	On error false is returned and the error code/string in the GX system
 *			is set appropriately. ( see gx_geterror() ) */
inline int cm_findengines(struct gxHANDLE handle, ENGNAME** pengines, int* nengine) {
	struct CM_FINDENGINES fe;
	fe.engines = pengines;
	fe.nengine = nengine;
	return gx_call(handle, CM_CALL_FINDENGINES, &fe);
}

/******************************************************************************/
/** Find the installed engines in the system. (ASCII version)
 *
 * By calling the cm_findenginesa() function the application can find the engines
 * in the GX system.
 *
 * \param handle	The gxHANDLE value retrieved by the gx_openmodule() function
 *					of the gxsd module.
 * \param pengines	Pointer to a buffer to store the name of the engines. The function
 *					reallocates the buffer for the names. To free the buffer use
 *					the gx_globalfree() function.
 * \param nengine	The number of the found engines.
 * \return	On error false is returned and the error code/string in the GX system
 *			is set appropriately. ( see gx_geterror() ) */
inline int cm_findenginesa(struct gxHANDLE handle, ENGNAMEA** pengines, int* nengine) {
	struct CM_FINDENGINESA fe;
	fe.engines = pengines;
	fe.nengine = nengine;
	return gx_call(handle, CM_CALL_FINDENGINESA, &fe);
}
//#endif 	/* WIN32 )*/

#endif	/* !GX_SWIGIF && !NO_GX_FUNCTIONS )*/

/******************************************************************************/
/** Gets the properties and their values of the current engine (optional).
 *
 * @param handle Handle of the module.
 * @param proplist Character buffer for properties.
 * @param sproplist Pointer to an integer value. As input, the sproplist is the size of the buffer. As output, 
 * it is the size of the buffer that is necessary for the property list. If there is not enough space, a GX_ERANGE error will occur.
 * @param separator Separator string to separate properties.
 * @param b_value  The function returns the property names with or without the values of the properties.
 * @return On error, false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ).*/
inline int cm_getengineproperties(gxHANDLE handle, wchar_t *proplist, int *sproplist, const wchar_t *separator, bool b_value)
{
int r;
struct CM_PARM_GETENGINEPROPERTIES gep;	
	gep.proplist = proplist;
	gep.sproplist = sproplist?*sproplist:0;
	gep.separator = separator;
	gep.b_value = b_value;
	r = gx_call(handle, CM_CALL_GETENGINEPROPERTIES, &gep);
	if (sproplist) *sproplist = gep.sproplist;
	return r;
}
/******************************************************************************/
/** Converting license plate text that contains Arabic letters according to the character order as on the license plate. 
 * This option is useful when displaying (or writing to file)the license plate characters in the original character order. 
 *
 * @param handle Handle of the module.
 * @param disptext Pointer to a memory area where to store the displayable lrtext.
 * @param sdisptext Size of the memory area in characters (not in bytes).
 * @param lrtext Text read from left to right.
 * @return On error, false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ).*/
inline int cm_lrtext2display(gxHANDLE handle, wchar_t *disptext, int sdisptext, const wchar_t *lrtext)
{
struct CM_PARM_LRTEXT2DISPLAY lrt;	
	lrt.disptext = disptext;
	lrt.sdisptext = sdisptext;
	lrt.lrtext = lrtext;
	return gx_call(handle, CM_CALL_LRTEXT2DISPLAY, &lrt);
}
/*******************************************************************************
 * Classes
 ******************************************************************************/
#ifdef GX_DOTNET
#pragma managed
#define	GX_ERROR_ENUM	GX_ERROR_CODES::
#else
#define	GX_ERROR_ENUM
#endif

#if !defined(NO_GX_CLASSES) && defined(__cplusplus) /*(*/
/******************************************************************************/
/** A character of the plate result */
/******************************************************************************/
GX_STRUCT cmCharacter {
	gxPG4	frame;		/**< Coordinates of the character tip frame. */
	int		bkcolor;	/**< Background color of the character tip. The color is in BGR format. */
	int		color;		/**< Color of the character tip. The color is in BGR format. */
	int		code;		/**< Code of the character in unicode type. */
	int		confidence;	/**< The confidence level of the character tip. */
};
/*******************************************************************************
 * The ANPR class
 *******************************************************************************/
/** Class for CMANPR functions.
 */
GX_CLASS cmAnpr : public gxHandle
#ifdef GX_DOTNET
, public System::IDisposable
#endif
{

#ifndef GX_SWIGIF
private:
	cmNP*	panprresult;	/**< Inner pointer to the \ref cmNP structure that holds the last result. */
#ifdef GX_DOTNET
	wchar_t *patxt2wtxt;	/**< Unicode conversion of the panprresult->text. */
#else
#endif
#endif
#ifndef GX_DOTNET
private:
	gxPG4	null_frame;		/**< To return the null frame. */
#endif

public:

	/** Class initialization with default properties. */
	inline cmAnpr() gxFuncThrowsError {
#ifndef GX_DOTNET
		if(!gx_openmodule(this, L"cmanpr", L"default")) gxthrow;
		memset((void*)&null_frame,0,sizeof(null_frame));
#else
		GX_GETHANDLE(h);
		if(!gx_openmodule(&h, L"cmanpr", L"default")) gxthrow;
		_set_handle(h.handle);
		patxt2wtxt = 0;
#endif
		panprresult = 0;
	}

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Class initialization with place of properties and name of the module (Unicode version).
	 *
	 * \param propname Place of properties in property tree (name of property group).
	 * \param modname Name of the module. */
	inline cmAnpr(const wchar_t *propname,
				const wchar_t *modname = (const wchar_t *)0) gxFuncThrowsError {

		if(!gx_openmodule(this, modname ? modname : L"cmanpr", propname)) gxthrow;
		panprresult = 0;
		memset(&null_frame,0,sizeof(null_frame));
	}

	/** Class initialization with place of properties and name of the module (ASCII version).
	 *
	 * \param propname Place of properties in property tree (name of property group).
	 * \param modname Name of the module. */
	inline cmAnpr(const char *propname,
				const char *modname = (const char *)0) gxFuncThrowsError {

		if(!gx_openmodule(this, modname ? modname : "cmanpr", propname)) gxthrow;
		panprresult = 0;
		memset(&null_frame,0,sizeof(null_frame));
	}
#endif

#ifdef GX_UNICODE
	/** Class initialization with place of properties (Unicode version).
	 *
	 * \param propname Place of properties in property tree (name of property group). */
	inline cmAnpr(gxInStr propname) gxFuncThrowsError {
		GX_GETSTRING(_propname, propname);
#ifndef GX_DOTNET
		if(!gx_openmodule(this, L"cmanpr", _propname)) gxthrow;
		memset(&null_frame,0,sizeof(null_frame));
#else
		GX_GETHANDLE(h);
		if(!gx_openmodule(&h, L"cmanpr", _propname)) gxthrow;
		_set_handle(h.handle);
		patxt2wtxt = 0;
#endif
		panprresult = 0;
	}
	/** Class initialization with place of properties and name of the module (Unicode version).
	 *
	 * \param propname Place of properties in property tree (name of property group).
	 * \param modname Name of the module. */
	inline cmAnpr(gxInStr propname, gxInStr modname) gxFuncThrowsError {
		GX_GETSTRING(_propname, propname);
		GX_GETSTRING(_modname, modname);
#ifndef GX_DOTNET
		if(!gx_openmodule(this, _modname, _propname)) gxthrow;
		memset(&null_frame,0,sizeof(null_frame));
#else
		GX_GETHANDLE(h);
		if(!gx_openmodule(&h, _modname, _propname)) gxthrow;
		_set_handle(h.handle);
		patxt2wtxt = 0;
#endif
		panprresult = 0;
	}
#endif

#ifdef GX_ASCII
	/** Class initialization with place of properties (ASCII version).
	 *
	 * \param propname Place of properties in property tree (name of property group). */
	inline cmAnpr(gxInAStr propname) gxFuncThrowsError {
		GX_GETASTRING(_propname, propname);
#ifndef GX_DOTNET
		if(!gx_openmodulea(this, "cmanpr", _propname)) gxthrow;
		memset(&null_frame,0,sizeof(null_frame));
#else
		GX_GETHANDLE(h);
		if(!gx_openmodulea(&h, "cmanpr", _propname)) gxthrow;
		_set_handle(h.handle);
		patxt2wtxt = 0;
#endif
		panprresult = 0;
	}
	/** Class initialization with place of properties and name of the module (Unicode version).
	 *
	 * \param propname Place of properties in property tree (name of property group).
	 * \param modname Name of the module. */
	inline cmAnpr(gxInAStr propname, gxInAStr modname) gxFuncThrowsError {
		GX_GETASTRING(_propname, propname);
		GX_GETASTRING(_modname, modname);
#ifndef GX_DOTNET
		if(!gx_openmodulea(this, _modname, _propname)) gxthrow;
		memset(&null_frame,0,sizeof(null_frame));
#else	
		GX_GETHANDLE(h);
		if(!gx_openmodulea(&h, _modname, _propname)) gxthrow;
		_set_handle(h.handle);
		patxt2wtxt = 0;
#endif
		panprresult = 0;
	}
#endif

	/** Class termination. */
	inline ~cmAnpr() {
		_Dispose();
	}

#ifdef GX_DOTNET_20
	inline !cmAnpr() {
		_Dispose();
	}
#else
	/** Disposes the class. */
	inline void Dispose(void) {
#ifdef GX_DOTNET
		System::GC::SuppressFinalize(this);
#endif
		_Dispose();
		/** go to base class */
		gxHandle::Dispose();
	}
#endif

private:
	inline void _Dispose(void) {
		if(panprresult) {gx_globalfree(panprresult); panprresult = 0;}
#ifdef GX_DOTNET
		if(patxt2wtxt) { free(patxt2wtxt); patxt2wtxt = 0; }
#endif
	}

public:

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET) /*(*/
	/** Reads the first number plate from the image.
	 *
	 * By calling the FindFirst() function the application can read a number plate
	 * from an image. The function returns the character tips of the number plate,
	 * and the text of the plate in ASCII and Unicode string format.
	 *
	 * \param pimage Points to the gxIMAGE structure which contains the image to be
	 *               scanned for number plates.
	 * \return True if plate found. On error false is returned or an exception is thrown. */
	inline bool FindFirst(const gxIMAGE *pimage) gxFuncThrowsError {
		bool st = cm_findfirst(*this, pimage, &panprresult) != 0;
#if defined(NO_GX_EXCEPTIONS)
		if (st) gx_seterror((int)GX_ERROR_ENUM GX_ENOERR);	
#else
		gxcondthrow(!st);
#endif
		return panprresult ? true : false;
	}
#endif	/* !GX_SWIGIF && !GX_DOTNET )*/

	/** Reads the first number plate from the image.
	 *
	 * By calling the FindFirst function the application can read a number plate
	 * from an image. The function returns the character tips of the number plate,
	 * and the text of the plate in ASCII and Unicode string format.
	 *
	 * \param img Reference to the an image which contains the image to be scanned for number plates.
	 * \return True if plate found. On error false is returned or an exception is thrown. */
	inline bool FindFirst(GX_CONST gxImageData GX_REF_CLASS(img)) gxFuncThrowsError {
#ifndef GX_DOTNET
		bool st = cm_findfirst(*this, img, &panprresult) != 0;
#else
		GX_GETHANDLE(h);
		if (patxt2wtxt) { free(patxt2wtxt); patxt2wtxt = 0; }
		cmNP *result = panprresult;
		gxIMAGE *i = (gxIMAGE *)img GX_M _get_image().ToPointer();
		bool st = cm_findfirst(h, i, &result) != 0;
		panprresult = result;
		if (panprresult && panprresult->text)
		{
		int s = (strlen(panprresult->text)+1)*sizeof(wchar_t);
			patxt2wtxt = (wchar_t*)malloc(s);
			if (!patxt2wtxt)
			{
				gx_seterror((int)GX_ERROR_ENUM GX_ENOMEM, L"[cmanpr] (text conversion)", 0);
				gxthrow;
			}
			memset(patxt2wtxt,0,s);
			gx_mbstowcs(patxt2wtxt,panprresult->text,strlen(panprresult->text)+1);		
		}
#endif
#if defined(NO_GX_EXCEPTIONS)
		if (st) gx_seterror((int)GX_ERROR_ENUM GX_ENOERR);	
#else
		gxcondthrow(!st);
#endif
		return panprresult ? true : false;
	}

	/** Reads the first number plate from the image.
	 *
	 * By calling the FindFirst function the application can read a number plate
	 * from an image. The function returns the character tips of the number plate,
	 * and the text of the plate in ASCII and Unicode string format.
	 *
	 * \param img Reference to an image which contains the image to be scanned for number plates.
	 * \return True if plate found. On error false is returned or an exception is thrown. */
	inline bool FindFirst(GX_CONST gxImage GX_REF_CLASS(img)) gxFuncThrowsError {
#ifndef GX_DOTNET
		bool st = cm_findfirst(*this, img, &panprresult) != 0;
#else
		GX_GETHANDLE(h);
		if (patxt2wtxt) { free(patxt2wtxt); patxt2wtxt = 0; }
		cmNP *result = panprresult;
		gxIMAGE *i = (gxIMAGE *)img GX_M _get_image().ToPointer();
		bool st = cm_findfirst(h, i, &result) != 0;
		panprresult = result;
		if (panprresult && panprresult->text)
		{
			patxt2wtxt = (wchar_t*)malloc((strlen(panprresult->text)+1)*sizeof(wchar_t));
			if (!patxt2wtxt)
			{
				gx_seterror((int)GX_ERROR_ENUM GX_ENOMEM, L"[cmanpr] (text conversion)", 0);
				gxthrow;
			}
			gx_mbstowcs(patxt2wtxt,panprresult->text,strlen(panprresult->text)+1);		
		}
#endif
#if defined(NO_GX_EXCEPTIONS)
		if (st) gx_seterror((int)GX_ERROR_ENUM GX_ENOERR);	
#else
		gxcondthrow(!st);
#endif
		return panprresult ? true : false;
	}

	/** Reads the next number plate from the image.
	 *
	 * By calling the FindNext() function the application can read additional
	 * number plates from an image. An error occurs if an application calls the
	 * FindNext() function before it calls the FindFirst() function. The function
	 * returns the character tips of the number plate, and the text of the plate in
	 * ASCII and Unicode string format.
	 *
	 * \return True if plate found. On error false is returned or an exception is thrown. */
	inline bool FindNext(void) gxFuncThrowsError {
#ifndef GX_DOTNET
		bool st = cm_findnext(*this, &panprresult) != 0;
#else
		GX_GETHANDLE(h);
		if (patxt2wtxt) { free(patxt2wtxt); patxt2wtxt = 0; }
		cmNP *result = panprresult;
		bool st = cm_findnext(h, &result) != 0;
		panprresult = result;
		if (panprresult && panprresult->text)
		{
			patxt2wtxt = (wchar_t*)malloc((strlen(panprresult->text)+1)*sizeof(wchar_t));
			if (!patxt2wtxt)
			{
				gx_seterror((int)GX_ERROR_ENUM GX_ENOMEM, L"[cmanpr] (text conversion)", 0);
				gxthrow;
			}
			gx_mbstowcs(patxt2wtxt,panprresult->text,strlen(panprresult->text)+1);		
		}
#endif
#if defined(NO_GX_EXCEPTIONS)
		if (st) gx_seterror((int)GX_ERROR_ENUM GX_ENOERR);	
#else
		gxcondthrow(!st);
#endif
		return panprresult ? true : false;
	}

	/** Reads the empty ADR plate from the image.
	 *
	 * By calling the FindEmptyAdr() function the application can read empty 
	 * ADR plate from an image. An error occurs if an application calls the
	 * FindEmptyAdr() function before it calls the FindFirst() function. 
	 *
	 * \return True if plate found. On error false is returned or an exception is thrown. */
	inline bool FindEmptyAdr()
	{
#ifndef GX_DOTNET
		bool st = cm_findemptyadr(*this, &panprresult) != 0;
#else
		GX_GETHANDLE(h);
		if (patxt2wtxt) { free(patxt2wtxt); patxt2wtxt = 0; }
		cmNP *result = panprresult;
		bool st = cm_findemptyadr(h, &result) != 0;
		panprresult = result;
#endif
#if defined(NO_GX_EXCEPTIONS)
		if (st) gx_seterror((int)GX_ERROR_ENUM GX_ENOERR);	
#else
		gxcondthrow(!st);
#endif
		return panprresult ? true : false;
	}

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Formats the number plate result from character tips.
	 *
	 * By calling the Format() function the application can create a number plate
	 * result from character tips. The application needs to call this function to
	 * retrieve the correct plate text if the number plate tips are changed. (for
	 * example: the program combines two or more number plate results)
	 *
	 * \param pimage Points to the gxIMAGE structure which contains the image to be scanned for number plates.
	 * \param ntip Number of the character tips.
	 * \param tips Points to the character tips.
	 * \return On error false is returned or an exception is thrown. */
	inline bool Format(const gxIMAGE* pimage, int ntip, const cmNP::CHR* tips) gxFuncThrowsError {
		bool st = cm_format(*this, pimage, ntip, tips, &panprresult) != 0;
		gxcondthrow(!st);
		return st;
	}

	/** Returns the last ANPR result.
	 *
	 * The class has a \ref cmNP pointer to store the number plate reading result.
	 *
	 * \return Pointer to the \ref cmNP structure that holds the last result. */
	inline cmNP* GetResult(void) const {
		return panprresult;
	}

	/** Returns the text of the last result (ASCII version).
	 *
	 * \return The text of the last result or NULL. */
	inline const char *GetTextA(void) const {
		return panprresult ? panprresult->text : (const char *)0;
	}

	/** Returns the text of the last result (Unicode version).
	 *
	 * \return The text of the last result or NULL. */
	inline const wchar_t *GetText(void) const {
		return panprresult ? panprresult->wtext : (const wchar_t *)0;
	}
#endif

#if defined(GX_SWIG) || defined(GX_DOTNET) /*(*/

#ifdef GX_UNICODE
	/** Returns the text of the last result (Unicode version).
	 *
	 * \return The text of the last result or an empty string. */
	inline gxOutStr GetText(void) GX_CONST {
		if(!panprresult || !(panprresult->wtext)) return GX_PUTSTRING_NONE;
		return GX_PUTSTRING(panprresult->wtext);
	}
#endif
#if defined(GX_DOTNET)
	/** Returns the ASCII text of the last result.
	 *
	 * \return The ASCII text of the last result or an empty string. */
	inline gxOutStr GetTextA(void) GX_CONST {
		if(!panprresult || !(panprresult->text) || !patxt2wtxt) return GX_PUTSTRING_NONE;
		return GX_PUTSTRING(patxt2wtxt);
	}
#endif

#ifdef GX_ASCII
	/** Returns the text of the last result (ASCII version).
	 *
	 * \return The text of the last result or an empty string. */
	inline gxOutAStr GetTextA(void) GX_CONST {
		if(!panprresult || !(panprresult->text)) return GX_PUTASTRING_NONE;
		return GX_PUTASTRING(panprresult->text);
	}
#endif

#endif /* GX_SWIG || GX_DOTNET )*/

private:
	/** Checks for available result.
	 *
	 * If no available result an exception is thrown. */
	inline bool _NoResultCheck(void) gxFuncThrowsError {
		if(panprresult) return true;
		gx_seterror((int)GX_ERROR_ENUM GX_EINVAL, L"[cmanpr] (!result)", 0);
		gxthrow;
		return false;
	}

public:
	/** Returns the coordinates of the plate frame.
	 *
	 * \return The coordinates of the plate frame. On error an empty structure is returned or an exception is thrown. */
#if defined(GX_SWIG)
	inline gxPG4* GetFrame(void) gxFuncThrowsError {
		if(_NoResultCheck()) return &(panprresult->frame);
		return &null_frame;
	}
#else
	inline gxPG4 GetFrame(void) gxFuncThrowsError {
		gxPG4 ret;
		if(_NoResultCheck()) {
			memcpy(&ret, &panprresult->frame, sizeof(ret));
		}else memset(&ret, 0, sizeof(ret));
		return ret;
	}
#endif

	/** Returns the background color of the plate.
	 *
	 * \return The background color in BGR format. On error -1 is returned or an exception is thrown. */
	inline int GetBkColor(void) gxFuncThrowsError {
		if(!_NoResultCheck()) return -1;
		return panprresult->bkcolor;
	}

	/** Returns the color of the plate.
	 *
	 * \return The plate color in BGR format. On error -1 is returned or an exception is thrown. */
	inline int GetColor(void) gxFuncThrowsError {
		if(!_NoResultCheck()) return -1;
		return panprresult->color;
	}

	/** Returns the confidence level of the plate.
	 *
	 * \return The confidence level. On error -1 is returned or an exception is thrown. */
	inline int GetConfidence(void) gxFuncThrowsError {
		if(!_NoResultCheck()) return -1;
		return panprresult->confidence;
	}

	/** Returns the type of the plate.
	 *
	 * \return The plate type. On error -1 is returned or an exception is thrown. */
	inline int GetType(void) gxFuncThrowsError {
		if(!_NoResultCheck()) return -1;
		return panprresult->type;
	}

	/** Returns the number of tips in the last result.
	 *
	 * \return The number of tips. On error -1 is returned or an exception is thrown. */
	inline int GetNTips(void) gxFuncThrowsError {
		if(!_NoResultCheck()) return -1;
		return panprresult->ntip;
	}

	/** Returns the requested character of the tip.
	 *
	 * \param ix Index of the character.
	 * \return The requested character. On error an empty structure is returned or an exception is thrown. */
	inline cmCharacter GetTip(int ix) gxFuncThrowsError {
		cmCharacter ret;
		if(!_NoResultCheck()) {
			memset(&ret, 0, sizeof(ret));
			return ret;
		}
		if((ix < 0)||(ix >= panprresult->ntip)) {
			gx_seterror((int)GX_ERROR_ENUM GX_EINVAL, L"[cmanpr] (0 <= ix < ntip)", 0);
			gxthrow;
			return ret;
		}
		memcpy(&ret, panprresult->tips+ix, sizeof(panprresult->tips[ix]));
		return ret;
	}

	/** Returns the number of characters in the last result.
	 *
	 * \return The number of characters. On error -1 is returned or an exception is thrown. */
	inline int GetNCharacters(void) gxFuncThrowsError {
		if(!_NoResultCheck()) return -1;
		return panprresult->ncharacter;
	}

	/** Returns the requested character of the last result.
	 *
	 * \param ix Index of the character.
	 * \return The requested character. On error an empty structure is returned or an exception is thrown. */
	inline cmCharacter GetCharacter(int ix) gxFuncThrowsError {
		cmCharacter ret;
		if(!_NoResultCheck()) {
			memset(&ret, 0, sizeof(ret));
			return ret;
		}
		if((ix < 0)||(ix >= panprresult->ncharacter)) {
			gx_seterror((int)GX_ERROR_ENUM GX_EINVAL, L"[cmanpr] (0 <= ix < ntip)", 0);
			gxthrow;
			return ret;
		}
		memcpy(&ret, panprresult->characters[ix], sizeof(*(panprresult->characters[ix])));
		return ret;
	}

//#ifdef WIN32 /*(*/

#if !defined(GX_DOTNET) && !defined(GX_SWIG) /*(*/

	/** Returns the installed engines in the system (Unicode version).
	 *
	 * By calling the FindEngines() function the application can list the engines installed.
	 *
	 * \param pengines	Pointer to a buffer to store the name of the engines. The function
	 *					reallocates the buffer for the names. To free the buffer use
	 *					the gx_globalfree() function.
	 * \param nengine	The number of the found engines.
	 * \return On error false is returned or an exception is thrown. */
	inline bool FindEngines(ENGNAME** pengines, int* nengine) gxFuncThrowsError {
		bool st = cm_findengines(*this, pengines, nengine) != 0;
		gxcondthrow(!st);
		return st;
	}

	/** Returns the installed engines in the system (ASCII version).
	 *
	 * By calling the FindEngines() function the application can find the engines installed.
	 *
	 * \param pengines	Pointer to a buffer to store the name of the engines. The function
	 *					reallocates the buffer for the names. To free the buffer use
	 *					the gx_globalfree() function.
	 * \param nengine	The number of the found engines.
	 * \return On error false is returned or an exception is thrown. */
	inline bool FindEngines(ENGNAMEA** pengines, int* nengine) gxFuncThrowsError {
		bool st = cm_findenginesa(*this, pengines, nengine) != 0;
		gxcondthrow(!st);
		return st;
	}
#endif	/* !GX_DOTNET || !GX_SWIG )*/

	/** Returns the installed engines in the system (Unicode version).
	 *
	 * \param max_engines The maximal number of engines in the array.
	 * \return The array of the names of engines found. On error an empty array is returned or an exception is thrown. */
	inline gxOutStrArray FindEngines(int max_engines GX_DEFARG(32)) gxFuncThrowsError {
		gxOutStrArray strarray;
		if(max_engines < 1) {
			gx_seterror((int)GX_ERROR_ENUM GX_EINVAL, L"[cmanpr] (0 < max_engines)", 0);
			gxthrow;
			return GX_PUTGSTRINGARRAY_NONE;
		}
		int nengines = max_engines;
		GX_GETHANDLE(h);
#if defined(GX_DOTNET) && !defined(GX_DOTNET_20)
		ENGNAME __nogc *names = 0;
#else
		ENGNAME *names = 0;
#endif
		bool st = cm_findengines(h, &names, &nengines) != 0;
		if(!st) {
			gxthrow;
			return GX_PUTGSTRINGARRAY_NONE;
		}
		if(!nengines) 
		{
			return GX_PUTGSTRINGARRAY_NONE;
		}
		wchar_t **_names = 0;
		st = gx_globalalloc((void**)&_names, sizeof(wchar_t *)*nengines) != 0;
		if(!st) {
			gx_globalfree(names);
			gxthrow;
			return GX_PUTGSTRINGARRAY_NONE;
		}
		for(int ix = 0; ix < nengines; ix++) _names[ix] = (wchar_t*)(&names[ix]);
		//gxOutStrArray 
		strarray = GX_PUTGSTRINGARRAY(_names, nengines, true);
		if(names) gx_globalfree(names);
		return strarray;
	}

#if !defined(GX_DOTNET) && !defined(GX_SWIG) /*(*/

	/** Gets the properties and their values of the current engine (optional).
	 *
	 * @param proplist Character buffer for properties.
	 * @param sproplist Pointer to an integer value. As input, the sproplist is the size of the buffer. As output, 
	 *					it is the size of the buffer that is necessary for the property list. If there is not enough space,
	 *					a GX_ERANGE error will occur.
	 * @param separator Separator string to separate properties.
	 * @param b_value  The function returns the property names with or without the values of the properties.
	 * @return On error, false is returned and the error code/string in the GX system
	 *         is set appropriately ( see gx_geterror() ).*/

	inline bool GetEngineProperties(wchar_t *proplist, int *sproplist, const wchar_t *separator, bool b_value) gxFuncThrowsError {
		bool st = cm_getengineproperties(*this, proplist, sproplist, separator, b_value) != 0;
		gxcondthrow(!st);
		return st;
	}

#endif	/* !GX_DOTNET || !GX_SWIG )*/

	/** Gets the properties and their values of the current engine (optional).
	 *
	 * @param b_value  The function returns the property names with or without the values of the properties.
	 * \return The array of the properties and their values. On error an empty array is returned or an exception is thrown. */
	inline gxOutStrArray GetEngineProperties(bool b_value) gxFuncThrowsError {
		gxOutStrArray strarray;
		GX_GETHANDLE(h);
		const wchar_t _separator[]=L"\r\n";
#if defined(GX_DOTNET) && !defined(GX_DOTNET_20)
		wchar_t __nogc *proplist = 0;
		wchar_t __nogc **props = 0;
#else
		wchar_t *proplist = 0;
		wchar_t **props = 0;
#endif
		int sproplist = 0;
		int i,nprops = 0;
		bool st = cm_getengineproperties(h, proplist, &sproplist, _separator, b_value) != 0;
		if(!st)
		{
			if (gx_geterror()!= (int)GX_ERROR_ENUM GX_ERANGE)
			{
				gxthrow;
				return GX_PUTGSTRINGARRAY_NONE;
			}
			st = gx_globalalloc((void**)&proplist, sizeof(wchar_t *)*sproplist) != 0;
			if(!st || !proplist) {
				gxthrow;
				return GX_PUTGSTRINGARRAY_NONE;
			}
			st = cm_getengineproperties(h, proplist, &sproplist, _separator, b_value) != 0;
		}
		if (!st)
		{
			if(proplist) { gx_globalfree(proplist); proplist = 0; }
			gxthrow;
			return GX_PUTGSTRINGARRAY_NONE;
		}
		wchar_t* p = proplist;
		wchar_t* pn;
		nprops = 0;
		while(p)
		{
			pn = wcsstr(p,_separator);
			if (pn) p = pn + wcslen(_separator);
			else p = pn;
			nprops ++;
		}
		st = gx_globalalloc((void**)&props, sizeof(wchar_t *)*nprops) != 0;
		if(!st || !props) 
		{
			if(proplist) { gx_globalfree(proplist); proplist = 0; }
			gxthrow;
			return GX_PUTGSTRINGARRAY_NONE;
		}
		p = proplist;
		i = 0;
		while(p && (i<nprops))
		{
			pn = wcsstr(p,_separator);
			if (pn) *pn = L'\0';
			props[i++] = p;
			if (pn) p = pn + wcslen(_separator);
			else p = pn;
		}
		strarray = GX_PUTGSTRINGARRAY(props, nprops, true);
		if(proplist) { gx_globalfree(proplist); proplist = 0; }
		if(props) { gx_globalfree(props); props = 0; }
		return strarray;
	}

#if !defined(GX_DOTNET) && !defined(GX_SWIG) /*(*/

	/** Converting license plate text that contains Arabic letters according to the character order as on the license plate. 
	 * This option is useful when displaying (or writing to file)the license plate characters in the original character order. 
	 *
	 * @param disptext Pointer to a memory area where to store the displayable lrtext.
	 * @param sdisptext Size of the memory area in characters (not in bytes).
	 * @param lrtext Text read from left to right.
	 * @return On error, false is returned and the error code/string in the GX system
	 *         is set appropriately ( see gx_geterror() ).*/

	inline bool LRText2Display(wchar_t *disptext, int sdisptext, const wchar_t *lrtext) gxFuncThrowsError {
		bool st = cm_lrtext2display(*this, disptext, sdisptext, lrtext) != 0;
		gxcondthrow(!st);
		return st;
	}

#endif	/* !GX_DOTNET || !GX_SWIG )*/

	/** Converting license plate text that contains Arabic letters according to the character order as on the license plate. 
	 * This option is useful when displaying (or writing to file)the license plate characters in the original character order. 
	 *
	 * @param lrtext Text read from left to right.
	 * @return The displayable lrtext. */

	inline gxOutStr LRText2Display(gxInStr lrtext) gxFuncThrowsError {
		wchar_t disptext[64]=L"";
		GX_GETHANDLE(h);
		GX_GETSTRING(_lrtext, lrtext);
		bool st = cm_lrtext2display(h, disptext, 64, _lrtext) != 0;
		gxcondthrow(!st);
		return GX_PUTSTRING(disptext);
	}

//#endif	/* WIN32 )*/

};

/******************************************************************************/
#endif /* NO_GX_CLASSES )*/
/******************************************************************************/
#ifdef GX_NAMESPACES
	}
#endif
/******************************************************************************/
#endif /* CMANPR_H_INCL */
/******************************************************************************/
