#pragma once
#include "Reader.h"
#include "../../graphics/Defines.h"
#include <algorithm>

namespace Jpeg2000
{
	//-------------------------------------------------------------------------------------------------------------------------------
	// Constant definitions
	//-------------------------------------------------------------------------------------------------------------------------------

#define MAX_PATH_LEN 4096 // Maximum length for file names

#define J2K_MAXRLVLS 33					    // Maximum number of decomposition levels
#define J2K_MAXBANDS (3 * J2K_MAXRLVLS - 2)	// Maximum number of areas associated with decomposition levels

#define J2K_MAXSSFTR 2    // Max SubSampling Factor (Values greater than 2 may result in an error)

	void* Malloc(size_t nSize);

	template<typename T>
	void  Free(T*& pMem)
	{
		if (NULL != pMem)
		{
			free(pMem);
			pMem = NULL;
		}
	}
	//-------------------------------------------------------------------------------------------------------------------------------
	// Enum definitions
	//-------------------------------------------------------------------------------------------------------------------------------

	// Progression order
	typedef enum EProgressionOrder
	{
		poUnknown = -1, // Unknown order
		poLRCP    =  0, // layer-resolution-component-precinct
		poRLCP    =  1, // resolution-layer-component-precinct
		poRPCL    =  2, // resolution-precinct-component-layer
		poPCRL    =  3, // precinct-component-resolution-layer
		poCPRL    =  4  // component-precinct-resolution-layer
	} ProgressionOrder;

	// Supported Color Spaces
	typedef enum EColorSpace
	{
		csUnknown = -1, // color space is undefined
		csRGB     =  1, // sRGB
		csGray    =  2, // Grayscale
		csYUV     =  3  // YUV
	} ColorSpace;

	// Supported Formats
	typedef enum ECodecFormat
	{
		codecUnknown = -1, // unknown codec
		codecJ2K     =  0, // JPEG-2000 codestream: read/write
		codecJPT     =  1, // JPT-stream (JPEG 2000, JPIP): read only
		codecJP2     =  2, // JPEG-2000 file format (Jp2-wrapper) : read/write
		codecMj2     =  3, // Motion JPEG-2000
	} CodecFormat;

	// Jpeg2000-Codestream decoding limitations
	typedef enum ELimitDecoding
	{
		declimNoLimitation      = 0, // There are no restrictions when decoding. We decode Jpeg2000-codestream completely
		declimLimitToMainHeader = 1	 // Decode only Main Header
	} LimitDecoding;

	//-------------------------------------------------------------------------------------------------------------------------------
	// Event (Message processing)
	//-------------------------------------------------------------------------------------------------------------------------------

#define EVT_ERROR	1 // Error
#define EVT_WARNING	2 // Warning
#define EVT_INFO	4 // Debug event

#define MSG_SIZE  512 // Maximum message size

#define JP2_ERROR_NO_ERROR           0x0000
#define JP2_ERROR_NOT_ENOUGH_MEMORY  0x0001


	//-------------------------------------------------------------------------------------------------------------------------------
	// Codec parameters (compression/decompression)
	//-------------------------------------------------------------------------------------------------------------------------------

	// Progression order changes (POC) (Annex A.6.6 Table A-32)
	typedef struct TPOC
	{
		int              nRSpoc;         // Resolution index for the start of a progression
		int              nCSpoc;         // Component index for the start of a progression.
		int              nLYEpoc;        // Layer index for the end of a progression
		int              nREpoc;         // Resolution index for the end of a progression
		int              nCEpoc;         // Component index for the end of a progression
		ProgressionOrder ePpoc;          // Progression order.
		int              nTile;
		char             sProgOrder[4];
	} POC;

	// Compression parameters
	typedef struct TEncoderParams
	{
		bool             bTileSizeOn;          // False: tile sizes aren't specified, true: tile sizes are specified
		int              nXTOsiz;              // XTOsiz
		int              nYTOsiz;              // YTOsiz
		int              nXTsiz;               // XTsiz
		int              nYTsiz;               // YTsiz
		int              nDistoAlloc;          // allocation by rate/distortion
		int              nFixedAlloc;          // allocation by fixed layer
		int              nFixedQuality;        // fixed_quality
		int             *pMatrix;              // fixed layer
		char            *sComment;             // Comment
		int              nCodingStyle;         // CodingStyle
		ProgressionOrder eProgOrder;           // Progression order (default LRCP)
		POC              aoPOC[32];            // Progression order changes
		int              nPOCsCount;           // Number of progression order changes (POC), default to 0
		int              nLayersCount;         // Number of layers
		float            afRates[100];         // Array of norms
		float            afDistoratio[100];    // Distortion Array
		int              nResolutionsCount;    // Number of resolutions (levels of decomposition)
		int              nCodeBlockWidthInit;  // Initial block width (standard 64)
		int              nCodeBlockHeightInit; // Initial block height (standard 64)
		int              nCodeBlockStyle;      // CodeBlockStyle
		int              nTransformId;         // 1: irreversible wavelet transform (Irreversible DTW), 0: lossless compression (standard)
		int              nROIComponentIndex;   // Region of interest: components affected [0..3], -1 means no ROI
		int              nROIShift;            // Region of interest: shift
		int              nPrecinctCount;                     // Number of areas
		int              anPrecinctWidthInit[J2K_MAXRLVLS];  // Initial area widths
		int              anPrecinctHeightInit[J2K_MAXRLVLS]; // Initial area heights

		int              nComponentsCount;       // Number of components in the source file
		char             sInFile[MAX_PATH_LEN];  // Source file name
		char             sOutfile[MAX_PATH_LEN]; // Result file name
		int              nIndexOn;               // Do create a file with indexing (according to standard 0)
		char             sIndex[MAX_PATH_LEN];   // Indexing file
		int              nImageOffsetX0;         // Shift the original image by X
		int              nImageOffsetY0;         // Shift the original image along Y
		int              nSubSamplingDx;         // SubSampling X         
		int              nSubSamplingDy;         // SubSampling Y
		int              nDecoderFormat;         // Source file format. 0:PGX, 1:PxM, 2:BMP
		int              nEncoderFormat;         // Output file format. 0: J2K, 1: JP2, 2: JPT
	} EncoderParams;

	// Decompression parameters
	typedef struct TDecoderParams
	{
		int           nReduce;                // If != 0, then the resolution of the original image is divided by 2^(nReduce). If == 0, or not used, then the image is decoded at full resolution.
		int           nLayer;                 // Set the maximum number of layers that we will decode.
		LimitDecoding eLimitDecoding;         // Decode the entire file, or just the header.

		char          sInFile[MAX_PATH_LEN];  // Source file name
		char          sOutfile[MAX_PATH_LEN]; // Result file name
		int           nDecoderFormat;         // Source file format. 0: J2k, 1: Jp2, 2: Jpt
		int           nEncoderFormat;         // Output file format. 0:PGX, 1:PxM, 2:BMP
	} DecoderParams;

	// Common fields for JPEG-2000 compression and decompression
	//EventManager *pEventManager;   /* Pointer to message handler (events) */\
		//void         *pClientData;     /* */\

#define CommonFields \
	bool          bIsDecompressor; /* To find out compression or decompression */\
	ECodecFormat  eCodecFormat;	   /* Selected codec */\
	void         *pJ2k;            /* Pointer to J2K codec */\
	void         *pJp2;            /* Pointer to JP2 codec */\
	void         *pMj2;            /* Pointer to JP2 codec */\
	int           nErrorCode       /* Error number */

	// Fields that are used for both reading and writing
	typedef struct TCommonStruct
	{
		CommonFields;
	} CommonStruct;

	typedef CommonStruct* PCommon;

	// Compression parameters
	typedef struct TCInfo
	{
		CommonFields; // General fields
		// Fields specific only to compression
	} CInfo;

	// Decompression parameters
	typedef struct TDInfo
	{
		CommonFields; // General fields
		// Fields characteristic only for decompression
	} DInfo;


	//-------------------------------------------------------------------------------------------------------------------------------
	// Image
	//-------------------------------------------------------------------------------------------------------------------------------

	typedef struct TImageComponent
	{
		int  nXRsiz;           // XRsiz: horizontal separation of the i-th component
		int  nYRsiz;           // YRsiz: vertical separation of the i-th component
		int  nWidth;           // Image width
		int  nHeight;          // Image height
		int  nXOsiz;           // Shift the component in X relative to the entire image
		int  nYOsiz;           // Shift of the component in Y relative to the entire image
		int  nPrecision;       // Precision
		int  nBPP;             // Bits Per Pixel
		int  nSigned;          // Signed - 1, unsigned - 0
		int  nDecodedResCount; // Number of Resolutions in an encoded image
		int  nFactorDiv2;      // The number of divisions into 2 of the resulting image, compared to the size of the original
		int *pData;            // Image data for i-th component
	} ImageComponent;

	typedef struct TImage
	{
		int             nXOsiz;      // XOsiz: horizontal shift from the starting point of the entire mesh to the area with the real image
		int             nYOsiz;      // YOsiz: vertical shift from the starting point of the entire mesh to the area with the real image
		int             nXsiz;       // Xsiz: grid width
		int             nYsiz;       // Ysiz: grid height
		int             nCsiz;       // Csiz: number of components in the image
		ColorSpace      eColorSpace; // Color space: sRGB, Greyscale or YUV
		ImageComponent *pComponents; // Image Components
	} Image;

	typedef struct TImageComponentParams
	{
		int nXRsiz;     // XRsiz: horizontal separation of the i-th component
		int nYRsiz;     // YRsiz: vertical separation of the i-th component
		int nWidth;     // Width
		int nHeight;    // Image height
		int nXoffset;   // Shift the component in X relative to the entire image
		int nYoffset;   // Shift of the component in Y relative to the entire image
		int nPrecision; // Precision
		int nBPP;       // Bits Per Pixel
		int nSigned;    // Signed - 1, unsigned - 0
	} ImageComponentParams;

	//-------------------------------------------------------------------------------------------------------------------------------
	// Tag-tree coder (TagTree.h)
	//-------------------------------------------------------------------------------------------------------------------------------

	// Tag node
	typedef struct TTagNode
	{
		struct TTagNode *pParent;
		int              nValue;
		int              nLow;
		int              nKnown;
	} TagNode;

	// Tag tree
	typedef struct TTagTree
	{
		int      nLeafsHorCount;
		int      nLeafsVerCount;
		int      nNodesCount;
		TagNode *pNodes;
	} TagTree;

	//-------------------------------------------------------------------------------------------------------------------------------
	//  JPEG2000 codestream (J2k.h)
	//-------------------------------------------------------------------------------------------------------------------------------

#define J2K_CP_CSTY_PRT 0x01 // CodingParams - CodingStyle - Partition (Tables A-20, A-23)
#define J2K_CP_CSTY_SOP 0x02
#define J2K_CP_CSTY_EPH 0x04

#define J2K_CCP_CSTY_PRT 0x01

#define J2K_CCP_CBLKSTY_LAZY    0x01
#define J2K_CCP_CBLKSTY_RESET   0x02
#define J2K_CCP_CBLKSTY_TERMALL 0x04
#define J2K_CCP_CBLKSTY_VSC     0x08
#define J2K_CCP_CBLKSTY_PTERM   0x10
#define J2K_CCP_CBLKSTY_SEGSYM  0x20

#define J2K_CCP_QNTSTY_NOQNT 0 // ComponentCodingParams - Quantization style - No quantization (Tables A-28, A-29)
#define J2K_CCP_QNTSTY_SIQNT 1 // ComponentCodingParams - Quantization style - Scalar implicit (Tables A-28, A-30)
#define J2K_CCP_QNTSTY_SEQNT 2 // ComponentCodingParams - Quantization style - Scalar explicit (Tables A-28, A-30)

	//-------------------------------------------------------------------------------------------------------------------------------

	// Marker Segments (Annex A.2 Table A-2)
#define J2K_MS_SOC 0xff4f	// SOC
#define J2K_MS_SOT 0xff90	// SOT
#define J2K_MS_SOD 0xff93	// SOD
#define J2K_MS_EOC 0xffd9	// EOC
#define J2K_MS_SIZ 0xff51	// SIZ
#define J2K_MS_COD 0xff52	// COD
#define J2K_MS_COC 0xff53	// COC
#define J2K_MS_RGN 0xff5e	// RGN
#define J2K_MS_QCD 0xff5c	// QCD
#define J2K_MS_QCC 0xff5d	// QCC
#define J2K_MS_POC 0xff5f	// POC
#define J2K_MS_TLM 0xff55	// TLM
#define J2K_MS_PLM 0xff57	// PLM
#define J2K_MS_PLT 0xff58	// PLT
#define J2K_MS_PPM 0xff60	// PPM
#define J2K_MS_PPT 0xff61	// PPT
#define J2K_MS_SOP 0xff91	// SOP
#define J2K_MS_EPH 0xff92	// EPH
#define J2K_MS_CRG 0xff63	// CRG
#define J2K_MS_COM 0xff64	// COM
	//////////////////////////////////////////////////
#define J2K_MS_EPC 0xff68	/**< EPC marker value (Part 11: JPEG 2000 for Wireless) */
#define J2K_MS_EPB 0xff66	/**< EPB marker value (Part 11: JPEG 2000 for Wireless) */ 
#define J2K_MS_ESD 0xff67	/**< ESD marker value (Part 11: JPEG 2000 for Wireless) */ 
#define J2K_MS_RED 0xff69	/**< RED marker value (Part 11: JPEG 2000 for Wireless) */
#define J2K_MS_SEC 0xff65    /**< SEC marker value (Part 8: Secure JPEG 2000) */
#define J2K_MS_INSEC 0xff94  /**< INSEC marker value (Part 8: Secure JPEG 2000) */

	//-------------------------------------------------------------------------------------------------------------------------------

	// Values that determine the decoding status (when the Main Header is decoded)
	typedef enum EJ2kStatus
	{
		j2kstateMHSOC  = 0x0001, // SOC marker
		j2kstateMHSIZ  = 0x0002, // SIZ marker
		j2kstateMH     = 0x0004, // The decoding process is in the Main Header
		j2kstateTPHSOT = 0x0008, // The decoding process is in the Tile Part Header and the SOT marker is now being read
		j2kstateTPH    = 0x0010, // The decoding process is in the Tile Part Header
		j2kstateMT     = 0x0020, // The EOC marker has just been read
		j2kstateNEOC   = 0x0040  // When decoding, we ignore the EOC marker because the codestream is truncated
	} J2kStatus;

	//-------------------------------------------------------------------------------------------------------------------------------

	// Quantization step size
	typedef struct TQuantStepSize
	{
		int nExponent;
		int nMantissa;
	} QuantStepSize;

	// Tile-component coding parameters (Annex A.6.2 Table A-23)
	typedef struct TTileCompCodingParams
	{
		int           nCodingStyle;                   // Coding style
		int           nResolutionsCount;              // Decomposition levels
		int           nCodeBlockWidth;                // Code-block size width
		int           nCodeBlockHeight;               // Code-block size height
		int           nCodeBlockStyle;                // Code-block context
		int           nTransformID;                   // Wavelet transform
		int           nQuantStyle;                    // Quantization type
		QuantStepSize aoStepSizes[J2K_MAXBANDS];      // Step size used for quantization
		int           nGuardBitsCount;                // Number of guard bits
		int           nROIShift;                      // SPrgn: Region Of Interest shift (Table A-25)
		int           anPrecinctWidth[J2K_MAXRLVLS];  // Precinct width
		int           anPrecinctHeight[J2K_MAXRLVLS]; // Precinct height	
	} TileCompCodingParams;

	// Tile coding parameters: this structure stores encoding/decoding parameters common to all tiles
	// (similar to COD, COC information in Main Header)
	typedef struct TTileCodingParams
	{
		int                   nFirst;            // Flag. 1 : first part-tile of this tile
		int                   nCodingStyle;      // Scod: Coding style (Table A-12)
		ProgressionOrder      eProgOrder;        // SPcod, Ppod: Progression order
		int                   nLayersCount;      // SPcod: Number of layers
		int                   nMCT;              // SPcod: Multiple component transform
		float                 afRates[100];      // Layer dimensions
		int                   nPOCsCount;        // Number of POC (progression order changes)
		int                   nUsePOC;           // Flag; whether we use a POC marker. 0 - no, 1 - yes.
		POC                   aoPOC[32];         // Progression order changes
		unsigned char        *pPPTData;          // Store a pointer to the Packet header in order to use it in Tier2 decoding
		unsigned char        *pPPTDataFirst;     // Pointer to the start of the first packet in the PacketHeader if PPT is used
		int                   nPPT;              // Flag. If a PPT marker is found for the current Tile, then the flag is 1.
		int                   nPPTStore;         // Use it if we found several PPT markers (we store their total length in bytes here)
		int                   nPPTLength;        // PPM bug 1
		float                 afDistoRatio[100]; // Add Fixed quality
		TileCompCodingParams *pTCCP;             // Tile-component coding parameters
	} TileCodingParams;

	// Coding parameters
	typedef struct TCodingParams
	{
		int               nDistoAlloc;    // allocation by rate/distortion
		int               nFixedAlloc;    // allocation by fixed layer
		int               nFixedQuality;  // Add Fixed quality
		int               nReduceFactor;  // If this value is different from 0, then the original resolution is divided by 2^(nReduceFactor); if equal to 0, or not used, decode the image at full resolution
		int               nLayerFactor;   // If this value is different from 0, then we decode only the first "layer"; if equal to 0, or not used, decode all "layers"
		LimitDecoding     eLimitDecoding; // Decoding restrictions.
		int               nIndexOn;       // 0 - no numbering, 1 - yes.
		int               nXTOsiz;        // XTOsiz: horizontal shift of the first Tile
		int               nYTOsiz;        // YTOsiz: vertical shift of the first Tile
		int               nXTsiz;         // XTsiz: width of one Tile in relation to the overall grid
		int               nYTsiz;         // YTsiz: height of one Tile in relation to the overall grid
		char             *sComment;       // Comment
		int               nXTilesCount;   // Number of Tiles horizontally
		int               nYTilesCount;   // Number of Tiles vertically
		int              *pTileIndex;     // Tiles serial numbers in codestream
		int               nTileIndexSize; // Array size pTileIndex
		unsigned char    *pPPMData;       // Store a pointer to the Packet header in order to use it in Tier2 decoding
		unsigned char    *pPPMDataFirst;  // Pointer to the start of the first packet in the PacketHeader if PPM is used
		int               nPPM;           // Flag. If a PPM marker is found for the current Tile, then the flag is equal to 1.
		int               nPPMStore;      // Use it if we found several PPM markers (we store their total length in bytes here)
		int               nPPMPrevious;   // Use it if we have found several PPM markers (the case if the previous PPM marker wasn't yet completed)
		int               nPPMLength;     // PPM bug 1
		TileCodingParams *pTCP;           // Tile coding parameters
		int              *pMatrix;        // Fixed layer
	} CodingParams;

	// Packet information in Tile
	typedef struct TPacketInfo
	{
		int    nStartPos; // Starting position
		int    nEndPos;   // End position
		double dDisto;
	} PacketInfo;

	// Information related to Tiles inside an image
	typedef struct TTileInfo
	{
		double     *pdThreshold;          // Threshold value for each layer
		int         nTileCount;           // Total number of Tiles
		int         nStartPos;            // Starting position
		int         nEndHeader;           // End position for header
		int         nEndPos;              // End position
		int         anXPrecinctCount[33]; // Number of areas (precinct) X for each resolution level
		int         anYPrecinctCount[33]; // Number of areas (precinct) in Y for each resolution level
		int         anPrecinctWidth[33];  // Area width (to the power of 2), for each resolution level
		int         anPrecinctHeight[33]; // Area height (to the power of 2), for each resolution level
		PacketInfo *pPacket;              // PacketInfo
		int         nNBPix;               // Add Fixed Quality
		double      dDistoTile;           // Add Fixed Quality
	} TileInfo;

	typedef struct TImageInfo
	{
		int              nIndexOn;        // 0 - no numbering, 1 - yes.
		double           dDistoMax;       // Maximum level of distortion reduction for the entire image
		int              nPacketCount;    // Number of packets
		int              nIndexWrite;     //
		int              nImageWidth;     // Image width
		int              nImageHeight;    // Image height
		ProgressionOrder eProgOrder;      // Progression Order
		int              nXTsiz;          // Tile size X
		int              nYTsiz;          // Tile size in Y
		int              nXTOsiz;         // Shift the first tile by X
		int              nYTOsiz;         // Y shift of the first tile
		int              nXTilesCount;    // Number of tiles by X
		int              nYTilesCount;    // Number of tiles in Y
		int              nCompCount;      // Number of components
		int              nLayersCount;    // Number of layers
		int              nDecompCount;    // Number of decomposition levels
		int              nMainHeadEnd;    // End position Main Header
		int              nCodestreamSize; // codestream size
		TileInfo        *pTile;           // TileInfo
	} ImageInfo;

	// JPEG-2000 codestream reader/writer
	typedef struct TJ2kCodestream
	{
		PCommon           pCodecInfo;     // General information for encoding and decoding
		int               nState;         // Here we store the current position of the Codestream decoder (Main header, Tile header, end of decoding)
		int               nCurTileIndex;  // Number of the current tile (i.e. which is currently being encoded/decoded)
		//unsigned char *pEndOfTile;     // Used to determine the position of the end of the tile in the codestream (to determine if the codestream is normal)
		int				  nSizeOfTile;
		int               nSOTStartPos;   // Save the initial position of the SOT marker so that after encoding the current tile we can return and record the length of this marker
		int               nSODStartPos;   // Likewise for the SOD marker
		int               nPosCorrection; // Needed to adjust the position, since the J2k file is written in several parts during encoding
		unsigned char   **ppTileData;     // An array with the data of all tiles
		int              *pTileLen;       // An array storing the data size for each tile
		TileCodingParams *pDefaultTCP;    // Used only during decompression: store general information for all tiles ( COD, COC )
		Image            *pImage;         // Pointer to the image being encoded or decoded
		CodingParams     *pCodingParams;  // Pointer to a structure storing encoding information
		ImageInfo        *pImageInfo;     // 
		CReader           *pStreamIO;      // Input / Output stream
	} J2kCodestream;

	//-------------------------------------------------------------------------------------------------------------------------------
	// Tile Coder/Decoder (Tile.h)
	//-------------------------------------------------------------------------------------------------------------------------------

	typedef struct TTCDSegment
	{
		int            nPassesCount;
		int            nLength;
		unsigned char *pData;
		int            nMaxPasses;
		int            nNewPassesCount;
		int            nNewLength;
	} TCDSegment;

	typedef struct TTCDPass
	{
		int            nRate;
		double         dDistortionDec;
		int            nTerm;
		int            nLen;
	} TCDPass;

	typedef struct TLayer
	{
		int            nPassesCount; // Number of passes
		int            nLen;         // Information length
		double         dDisto;       // Deviation
		unsigned char *pData;        // Data
	} Layer;

	typedef struct TCodeBlock
	{
		int           nX0;                  // CodeBlock Dimensions
		int           nY0;                  // (x0, y0) - upper left corner
		int           nX1;                  // (x1, y1) - lower right corner
		int           nY1;                  // 
		int           nBPSCount;            //
		int           nLenBitsCount;        //
		int           nLen;                 // Length
		int           nPassesCount;         // Number of passes already completed for this CodeBlock
		int           nNewPassesCount;      // Number of passes added to this CodeBlock
		int           nSegmentsCount;       // Number of segments
		TCDSegment    aSegments[100];		// The segments themselves
		unsigned char  aData[8192];			 // Data
		int           nPassesCountInLayers; // Number of passes in the layer
		Layer         aLayers[100];				// Layer information
		int           nTotalPassesCount;    // Total number of passes
		TCDPass       aPasses[100];         // Information about passes
	} CodeBlock;

	typedef struct TPrecinct
	{
		int        nX0;            // Dimensions Precinct
		int        nY0;            // (x0, y0) - upper left corner
		int        nX1;            // (x1, y1) - lower right corner
		int        nY1;            // 
		int        nCountInWidth;  // Number of blocks wide
		int        nCountInHeight; // Number of blocks in height
		CodeBlock *pCodeBlocks;    // CodeBlocks
		TagTree   *pInclTree;      // Inclusion tree
		TagTree   *pIMSBTree;      // IMSB tree
	} Precinct;

	typedef struct TBand
	{
		int       nX0;        // Band sizes
		int       nY0;        // (x0, y0) - upper left corner
		int       nX1;        // (x1, y1) - lower right corner
		int       nY1;        // 
		int       nBandIndex; // Current Band number
		Precinct *pPrecincts; // Information about the areas (Precinct) included in this Band
		int       nBPSCount;  //
		float     fStepSize;  //
	} Band;

	typedef struct TResolution
	{
		int  nX0;         // Dimensions Resolution
		int  nY0;         // (x0, y0) - upper left corner
		int  nX1;         // (x1, y1) - lower right corner
		int  nY1;         // 
		int  nPrecCountW; // Number of areas (Precinct) by width
		int  nPrecCountH; // Number of areas (Precinct) by height
		int  nBandsCount; // Sub-band quantity
		Band aBands[3];   // Sub-bands
	} Resolution;

	typedef struct TTileComp
	{
		int         nX0;               // TileComp Dimensions
		int         nY0;               // (x0, y0) - upper left corner
		int         nX1;               // (x1, y1) - lower right corner
		int         nY1;               // 
		int         nResolutionsCount; // Number of resolutions
		Resolution *pResolutions;      // Resolutions
		int        *pData;             // Component data
		int         nNBPix;            // Fixed_quality
	} TileComp;

	typedef struct TTile
	{
		int       nX0;               // Tile sizes
		int       nY0;               // (x0, y0) - upper left corner
		int       nX1;               // (x1, y1) - lower right corner
		int       nY1;               // 
		int       nComponentsCount;  // Number of components
		TileComp *pComponents;       // Components
		int       nNBPix;            // Fixed_quality
		double    dDistoTile;        // Fixed_quality
		double    adDistoLayer[100]; // Fixed_quality
	} Tile;

	typedef struct TTCDImage
	{
		int   nTilesCountW; // Number of tiles by width
		int   nTilesCountH; // Number of tiles by height
		Tile *pTiles;       // Tiles
	} TCDImage;

	typedef struct TTCD
	{
		PCommon           pCodecInfo;    // Codec information
		TCDImage         *pTCDImage;     // Encoded Image
		Image            *pImage;        // Image
		CodingParams     *pCodingParams; // Options
		Tile             *pTCDTile;      // Pointer to the current tile being encoded/decoded
		TileCodingParams *pTCP;          // Encoding/decoding options for all tiles
		int               nTCDTileIndex; // Number of the current encoded/decoded tile
	} TCD;

	//-------------------------------------------------------------------------------------------------------------------------------
	// Jp2 file format (Jp2.h)
	//-------------------------------------------------------------------------------------------------------------------------------

#define JPIP_JPIP 0x6a706970

	// Jp2 boxes (Table I-2)
#define JP2_JP   0x6a502020 // JPEG 2000 signature box
#define JP2_PRFL 0x7072666c // Profile box
#define JP2_FTYP 0x66747970 // File type box
#define JP2_JP2H 0x6a703268 // JP2 header box
#define JP2_IHDR 0x69686472 // Image header box
#define JP2_COLR 0x636f6c72 // Colour specification box
#define JP2_JP2C 0x6a703263 // Contiguous codestream box
#define JP2_URL  0x75726c20 // URL box
#define JP2_DBTL 0x6474626c // ???
#define JP2_BPCC 0x62706363 // Bits per component box
#define JP2_JP2  0x6a703220 // File type fields
#define JP2_CDEF 0x63646566 // Component Definition box

	//-------------------------------------------------------------------------------------------------------------------------------

	// Jp2 component
	typedef struct TJp2Component
	{
		int nDepth;
		int nSigned;
		int nBPCC;
	} Jp2Component;

	typedef struct TJp2Color
	{
		BYTE *icc_profile_buf;
		DWORD icc_profile_len;

		//opj_jp2_cdef_t *jp2_cdef;
		//opj_jp2_pclr_t *jp2_pclr;

		bool has_colr;
	} Jp2Color;

	// Jp2 file format reader/writer
	typedef struct TJp2Stream
	{
		PCommon        pCodecInfo;       // General information for encoding and decoding
		J2kCodestream *pJ2k;             // Pointer to structure to read/write JPEG2000 Codestream

		unsigned int   nWidth;           // Image width
		unsigned int   nHeight;          // Image height
		unsigned int   nComponentsCount; // Number of components
		unsigned int   nBPC;             // Bits per component
		unsigned int   nCompressionType; // CompressionType
		unsigned int   nColorSpaceUnk;   // Colourspace Unknown
		unsigned int   nIPR;             // Intellectual Property

		unsigned int   nMethod;          // Color specification method
		unsigned int   nPrec;            // Precedence
		unsigned int   nApprox;          // Colourspace approximation
		unsigned int   nEnumCS;          // Enumerated colourspace

		unsigned int   nBrand;           // Brand
		unsigned int   nMinVersion;      // MinVersion
		unsigned int   nCompListLength;  // Compatibility list length
		unsigned int  *pCompList;        // Compatibility list

		Jp2Component  *pComponents;
		unsigned int   nJ2kCodestreamOffset;
		unsigned int   nJ2kCodestreamLength;

		Jp2Color	   oColor;
	} Jp2Stream;

	// Jp2 Box
	typedef struct TJp2Box
	{
		int nLength;
		int nType;
		int nInitPos;
	} Jp2Box;

	//-------------------------------------------------------------------------------------------------------------------------------
	// MQ-coder (ArithmeticCoder.h)
	//-------------------------------------------------------------------------------------------------------------------------------

	// See Annex C. fcd15444-1.pdf (MQ-coder Encoder/Decoder)

#define MQC_NUMCTXS 32

	typedef struct TMQCoderState
	{
		unsigned int          nLPSValue; // probability for the Least Probable Symbol (0.75->0x8000, 1.5->0xffff)
		int                   nMPS;      // Most Probable Symbol (0 or 1)
		struct TMQCoderState *pNextMPS;  // Pointer to the next state if the next MPS symbol is encoded
		struct TMQCoderState *pNextLPS;  // Pointer to the next state if the next LPS symbol is encoded
	} MQCoderState;

	// MQ-coder
	typedef struct TMQCoder
	{
		unsigned int   nCregister;
		unsigned int   nAregister;
		unsigned int   nCt;

		unsigned char *pBufferPointer;
		unsigned char *pStart;
		unsigned char *pEnd;
		MQCoderState  *pContexts[MQC_NUMCTXS];
		MQCoderState **ppCurContext;
	} MQCoder;

	//-------------------------------------------------------------------------------------------------------------------------------
	// Raw (Raw.h)
	//-------------------------------------------------------------------------------------------------------------------------------

	typedef struct TRaw
	{
		unsigned char  nBuffer;        // Temporary buffer in which bit encoding/decoding occurs
		unsigned int   nFreeBitsCount; // Number of bits free to read or write
		unsigned int   nMaxLen;        // Maximum length for decoding
		unsigned int   nLen;           // Length of decoded information
		unsigned char *pBufferPointer; // Pointer to the current position in the buffer
		unsigned char *pBufferStart;   // Pointer to the beginning of the buffer
		unsigned char *pBufferEnd;     // Pointer to the end of the buffer
	} Raw;

	//-------------------------------------------------------------------------------------------------------------------------------
	// Jpt (Jpt.h)
	//-------------------------------------------------------------------------------------------------------------------------------

	// Message Header JPT stream structure
	typedef struct TJPTMessageHeader
	{
		unsigned int nId;            // In-class Identifier
		unsigned int nLastByte;      // Last byte information
		unsigned int nClassId;       // Class Identifier
		unsigned int nCSnId;         // CSn : index identifier
		unsigned int nMessageOffset; // Message offset
		unsigned int nMessageLength; // Message length
		unsigned int nLayerNB;       // Auxiliary for JPP case
	} JPTMessageHeader;

	//-------------------------------------------------------------------------------------------------------------------------------
	// Packet Iterator 
	//-------------------------------------------------------------------------------------------------------------------------------

	typedef struct TPacketResolution
	{
		int nDx;
		int nDy;
		int nWidth;
		int nHeight;
	} PacketResolution;

	typedef struct TPacketComponent
	{
		int               nDx;
		int               nDy;
		int               nResolutionsCount;
		PacketResolution *pResolutions;
	} PacketComponent;

	typedef struct TPacketIterator
	{
		short int       *pInclude;         // Flag indicating whether this packet has been used (used in POC)
		int              nStepLayer;       // LayerStep is used to localize the packet into pInclude
		int              nStepResolution;  // ResolutionStep is used to localize the packet into pInclude
		int              nStepComponent;   // ComponentStep is used to localize the packet into pInclude
		int              nStepPrecinct;    // PrecinctStep is used to localize the packet into pInclude

		int              nIndexComponent;  // Component number for packet definition
		int              nIndexResolution; // Level of detail number for packet definition
		int              nIndexPrecinct;   // Area number for packet definition
		int              nIndexLayer;      // Layer number to identify the packet

		int              nFirst;           // Flag indicating whether this is the first packet
		POC              oPOC;             // Progression Order Change
		int              nComponentsCount; // Number of components

		PacketComponent *pComponents;
		int              nTileX0;          //
		int              nTileY0;          // Boundaries of the current tile
		int              nTileX1;          //
		int              nTileY1;          //
		int              nX;
		int              nY;
		int              nDx;
		int              nDy;
	} PacketIterator;

	//-------------------------------------------------------------------------------------------------------------------------------
	//  Tier-1 coding (coefficient coding)
	//-------------------------------------------------------------------------------------------------------------------------------

#define T1_NMSEDEC_BITS 7

#define T1_MAXCBLKW 1024	// Maximum CodeBlock size (width)
#define T1_MAXCBLKH 1024	// Maximum CodeBlock size (height)

#define T1_SIG_NE 0x0001	// Context orientation: Northeast direction
#define T1_SIG_SE 0x0002	// Context orientation: southeast direction
#define T1_SIG_SW 0x0004	// Context orientation: southwest direction
#define T1_SIG_NW 0x0008	// Context orientation: northwest direction
#define T1_SIG_N  0x0010	// Context orientation: North direction
#define T1_SIG_E  0x0020	// Context orientation: east direction
#define T1_SIG_S  0x0040	// Context orientation: south direction
#define T1_SIG_W  0x0080	// Context orientation: west direction
#define T1_SIG_OTH  (T1_SIG_N|T1_SIG_NE|T1_SIG_E|T1_SIG_SE|T1_SIG_S|T1_SIG_SW|T1_SIG_W|T1_SIG_NW)
#define T1_SIG_PRIM (T1_SIG_N|T1_SIG_E|T1_SIG_S|T1_SIG_W)

#define T1_SGN_N 0x0100
#define T1_SGN_E 0x0200
#define T1_SGN_S 0x0400
#define T1_SGN_W 0x0800
#define T1_SGN (T1_SGN_N|T1_SGN_E|T1_SGN_S|T1_SGN_W)

#define T1_SIG    0x1000
#define T1_REFINE 0x2000
#define T1_VISIT  0x4000

#define T1_NUMCTXS_ZC 9
#define T1_NUMCTXS_SC 5
#define T1_NUMCTXS_MAG 3
#define T1_NUMCTXS_AGG 1
#define T1_NUMCTXS_UNI 1

#define T1_CTXNO_ZC 0
#define T1_CTXNO_SC  (T1_CTXNO_ZC  + T1_NUMCTXS_ZC )
#define T1_CTXNO_MAG (T1_CTXNO_SC  + T1_NUMCTXS_SC )
#define T1_CTXNO_AGG (T1_CTXNO_MAG + T1_NUMCTXS_MAG)
#define T1_CTXNO_UNI (T1_CTXNO_AGG + T1_NUMCTXS_AGG)
#define T1_NUMCTXS   (T1_CTXNO_UNI + T1_NUMCTXS_UNI)

#define T1_NMSEDEC_FRACBITS (T1_NMSEDEC_BITS - 1)

#define T1_TYPE_MQ  0  // Normal coding, using Arithmetic entropy coding (Annex C)
#define T1_TYPE_RAW 1  // There is no coding, the information in Codestream is contained in raw form

	//-------------------------------------------------------------------------------------------------------------------------------

	typedef struct TTier1
	{
		PCommon  pCodecInfo;  // Codec information
		MQCoder *pMQCoder;    // Pointer to a structure for reading/writing MQ-encoded data
		Raw     *pRaw;        // Pointer to a structure for reading/writing unencoded data

		int      lut_ctxno_zc[1024];
		int      lut_ctxno_sc[256];
		int      lut_ctxno_mag[4096];
		int      lut_spb[256];
		int      lut_nmsedec_sig[1 << T1_NMSEDEC_BITS];
		int      lut_nmsedec_sig0[1 << T1_NMSEDEC_BITS];
		int      lut_nmsedec_ref[1 << T1_NMSEDEC_BITS];
		int      lut_nmsedec_ref0[1 << T1_NMSEDEC_BITS];

		int      aData[T1_MAXCBLKH][T1_MAXCBLKW];          // codeblock data
		int      aFlags[T1_MAXCBLKH + 2][T1_MAXCBLKH + 2]; // Flags

	} Tier1;

	//-------------------------------------------------------------------------------------------------------------------------------
	//  Tier-2 coding
	//-------------------------------------------------------------------------------------------------------------------------------

	typedef struct TTier2
	{
		PCommon       pCodecInfo;
		Image        *pImage;        // Encoding: pointer to the source image. Decoding: pointer to the resulting image.
		CodingParams *pCodingParams;
	} Tier2;

	//-------------------------------------------------------------------------------------------------------------------------------
	// Mj2 file format (Mj2.h)
	//-------------------------------------------------------------------------------------------------------------------------------

#define MJ2_JP    0x6a502020
#define MJ2_FTYP  0x66747970
#define MJ2_MJ2   0x6d6a7032
#define MJ2_MJ2S  0x6d6a3273
#define MJ2_MDAT  0x6d646174
#define MJ2_MOOV  0x6d6f6f76
#define MJ2_MVHD  0x6d766864
#define MJ2_TRAK  0x7472616b
#define MJ2_TKHD  0x746b6864
#define MJ2_MDIA  0x6d646961
#define MJ2_MDHD  0x6d646864
#define MJ2_MHDR  0x6d686472
#define MJ2_HDLR  0x68646C72
#define MJ2_MINF  0x6d696e66
#define MJ2_VMHD  0x766d6864
#define MJ2_SMHD  0x736d6864
#define MJ2_HMHD  0x686d6864
#define MJ2_DINF  0x64696e66
#define MJ2_DREF  0x64726566
#define MJ2_URL   0x75726c20
#define MJ2_URN   0x75726e20
#define MJ2_STBL  0x7374626c
#define MJ2_STSD  0x73747364
#define MJ2_STTS  0x73747473
#define MJ2_STSC  0x73747363
#define MJ2_STSZ  0x7374737a
#define MJ2_STCO  0x7374636f
#define MJ2_MOOF  0x6d6f6f66
#define MJ2_FREE  0x66726565
#define MJ2_SKIP  0x736b6970
#define MJ2_JP2C  0x6a703263
#define MJ2_FIEL  0x6669656c
#define MJ2_JP2P  0x6a703270
#define MJ2_JP2X  0x6a703278
#define MJ2_JSUB  0x6a737562
#define MJ2_ORFO  0x6f72666f
#define MJ2_MVEX  0x6d766578
#define MJ2_JP2   0x6a703220
#define MJ2_J2P0  0x4a325030

	// Decompressed format used in parameters YUV = 0
#define YUV_DFMT 1 

	// Compressed format used in parameters MJ2 = 0
#define MJ2_CFMT 2


	//-------------------------------------------------------------------------------------------------------------------------------

	// Time To Sample
	typedef struct TMj2_TimeToSample
	{
		int nSampleCount;
		int nSampleDelta;
	} Mj2_TimeToSample;

	// Chunk
	typedef struct TMj2_Chunk
	{
		int nNumSamples;
		int nSampleDescriptionIndex;
		int nOffset;
	} Mj2_Chunk;

	// Sample to chunk
	typedef struct TMj2_SampleToChunk
	{
		int nFirstChunk;
		int nSamplesPerChunk;
		int nSampleDescriptionIndex;
	} Mj2_SampleToChunk;

	// Sample 
	typedef struct TMj2_Sample
	{
		unsigned int unSampleSize;
		unsigned int unOffset;
		unsigned int unSampleDelta;
	} Mj2_Sample;

	// URL
	typedef struct TMj2_Url
	{
		int anLocation[4];
	} Mj2_Url;

	// URN
	typedef struct TMj2_Urn
	{
		int anName[4];
		int anLocation[4];
	} Mj2_Urn;

	// Image Track Parameters
	typedef struct TMj2_TrackParams
	{
		PCommon           pCodecInfo;
		int               nTrackID;
		int               nTrackType;
		unsigned int      unCreationTime;
		unsigned int      unModificationTime;
		int               nDuration;
		int               nTimescale;
		int               nLayer;
		int               nVolume;
		int               nLanguage;
		int               nBalance;
		int               nMaxPDUsize;
		int               nAvgPDUsize;
		int               nMaxBitrate;
		int               nAvgBitrate;
		int               nSlidingAvgBitrate;
		int               nGraphicsMode;
		int               anOpColor[3];
		int               nNumUrl;
		Mj2_Url*          pUrl;
		int               nNumUrn;
		Mj2_Urn*          pUrn;
		int               anDim[2];
		int               nWidth;
		int               nHeight;
		int               nVisualWidth;
		int               nVisualHeight;
		int               nCbCr_SubSampling_dx;
		int               nCbCr_SubSampling_dy;
		int               nSampleRate;
		int               nSampleDescription;
		int               nHorResolution;
		int               nVerResolution;
		int               anCompressorName[8];
		int               nDepth;
		unsigned char     unFieldCount;
		unsigned char     unFieldOrder;
		unsigned char     unOr_FieldCount;
		unsigned char     unOr_FieldOrder;
		int               nNumBr;
		unsigned int*     pBr;
		unsigned char     unNumJp2x;
		unsigned char*    pJp2xData;
		unsigned char     unHsub;
		unsigned char     unVsub;
		unsigned char     unHoff;
		unsigned char     unVoff;
		int               anTransMatrix[9];
		unsigned int      unNumSamples;       // Number of samples
		int               nTransorm;
		int               nHandlerType;
		int               nNameSize;
		unsigned char     unSameSampleSize;
		int               nNumTimeToSample;
		Mj2_TimeToSample* pTimeToSample;      // Time to sample
		unsigned int      unNumChunks;
		Mj2_Chunk*        pChunk;
		int               nNumSamplesToChunk;
		Mj2_SampleToChunk*pSampleToChunk;
		char*             sName;
		Jp2Stream         oJp2;
		Mj2_Sample       *pSample;             // Sample parameters
	} Mj2_TrackParams;

	// MJ2 box
	typedef struct TMj2_Box
	{
		int nLength;
		int nType;
		int nInitPos;
	} Mj2_Box;

	// MJ2 Movie
	typedef struct TMj2_Movie
	{
		PCommon          pCodecInfo;
		J2kCodestream*   pJ2k;
		unsigned int     unBrand;
		unsigned int     unMinVersion;
		int              nCompListLength;
		unsigned int*    pCompList;
		unsigned int     unCreationTime;
		unsigned int     unModificationTime;
		int              nTimescale;
		unsigned int     unDuration;
		int              nRate;
		int              nNumVtk;
		int              nNumStk;
		int              nNumHtk;
		int              nVolume;
		int              anTransMatrix[9];
		int              nNextTrackId;
		Mj2_TrackParams* pTrack;
	} Mj2_Movie;

	// Compression parameters
	typedef struct TMj2_EncoderParameters
	{
		TEncoderParams pJ2k_Parameters;
		int            nDecoderFormat;       // input file format 0:MJ2
		int            nEncoderFormat;       // output file format 0:YUV
		int            anDim[2];             // Portion of the image coded
		int            nWidth;               // YUV Frame width
		int            nHeight;              // YUV Frame height
		int            nCbCr_SubSampling_dx; // Sample rate of YUV 4:4:4, 4:2:2 or 4:2:0	
		int            nCbCr_SubSampling_dy; // Sample rate of YUV 4:4:4, 4:2:2 or 4:2:0
		int            nFrameRate;           //   Image Frame Rate
		int            nNumComps;            // In YUV files, numcomps always considered as 3
		int            nPrec;                // In YUV files, precision always considered as 8
	} Mj2_EncoderParameters;


	// Bit input-output stream (BitIO)
	//-------------------------------------------------------------------------------------------------------------------------------

	typedef struct TBitIO
	{
		unsigned char *pStart;          // Pointer to the beginning of the buffer
		unsigned char *pEnd;            // Pointer to the end of the buffer
		unsigned char *pCurPos;         // Pointer to the current position in the buffer
		unsigned int   nBuffer;         // Buffer
		int            nValidBitsCount; // Coder: number of free bits to write
		// Decoder: number of available bits to read
	} BitIO;
}
