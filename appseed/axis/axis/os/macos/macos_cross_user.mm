#import "macos_mm.h"


const char * mm_keyboard_input_source()
{
   
   TISInputSourceRef source = TISCopyCurrentKeyboardInputSource();
   NSString *s = (__bridge NSString *)(TISGetInputSourceProperty(source, kTISPropertyInputSourceID));
   
   if(s == nil)
      return strdup("");
   
   return strdup([s UTF8String]);
}