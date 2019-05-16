//===============================================
// DragonFireSDK.h
//===============================================

int WorldSetxy(int x,int y);

int ImageAdd(char *filename);

int ViewAdd(int im,int x,int y);
int ViewAdd(char *filename,int x,int y);
int ViewAdd(char *filename,int x,int y,int (*callback)(int id,int event,int x,int y),int id);

int ViewGetx(int vw);
int ViewGety(int vw);

int ViewSetxy(int vw,int x,int y);
int ViewSetImage(int vw,int im);
int ViewSetVisible(int vw,int flag);

int TouchAdd(int x,int y,int width,int height,int (*callback)(int id,int event,int x,int y),int id); // event: 1=down, 2=move, 3=up
int TouchGetxy(int i,int &x,int &y);

void RandomSetSeed(unsigned int seed);
void Randomize();
int Random(unsigned int range); // ret number from 0 to <range

int ButtonAdd(char *filename,int x,int y,int (*callback)(int id),int id);
int PushButtonAdd(char *filename,int x,int y,int (*callback)(int id),int id);

int FontAdd(char *foldername);

int TextAdd(int x,int y,char *text,int font);
int TextSetText(int tx,char *text);
int TextSetxy(int tx,int x,int y);
int TextGetx(int tx);
int TextGety(int tx);

int FileOpenResource(char *filename);
int FileOpen(char *filename);
int FileCreate(char *filename);
int FileRead(int fh,char *buf,int len);
int FileWrite(int fh,char *buf,int len);
int FileSeek(int fh,int seek);
int FileClose(int fh);

int SoundAdd(char *filename);
int SoundPlay(int sn);


void DeckShuffle(int deck[52]);

void printf(char* lpszFormat, ...);
void sprintf(char *szBuffer,char* lpszFormat, ...);

void StrCopy(char *name,char *filename);
void StrAppend(char *name,char *filename);

void LandscapeMode();
void PortraitMode();

int ViewSetRotate(int vw,int degrees);
int ViewSetSize(int vw,int width,int height);

int ViewSetTouch(int vw,int tc);

int TiltGetx();
int TiltGety();
int TiltGetz();
