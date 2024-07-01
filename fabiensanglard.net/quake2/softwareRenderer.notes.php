<html><head>    <title>Quake 2 methods tree unrolled</title>    

<meta http-equiv="Content-Type" content="text/html; utf-8">    
<style type="text/css">        body         {            font-family: courier new;            font-size: 10pt;            color: 00000;        }    </style>        

<script type="text/javascript">        var gaJsHost = (("https:" == document.location.protocol) ? "https://ssl." : "http://www.");        
document.write("\<script src='&quot;&#32;+&#32;gaJsHost&#32;+&#32;&quot;google-analytics.com/ga.js' type='text/javascript'>\<\/script>" );    </script>    
<script type="text/javascript">        var pageTracker = _gat._getTracker("UA-3217394-1");        pageTracker._initData();        
pageTracker._trackPageview();    </script>    <script type="text/javascript">        var gaJsHost = (("https:" == document.location.protocol) ? "https://ssl." : "http://www.");        
document.write(unescape("%3Cscript src='" + gaJsHost + "google-analytics.com/ga.js' type='text/javascript'%3E%3C/script%3E"));    </script>    
<script type="text/javascript">        var pageTracker = _gat._getTracker("UA-3217394-2");        pageTracker._trackPageview();</script></head><body>

<pre>

userful commands

    VIDEO GEN:
    ==========
        sw_drawflat 1
        crosshair 0
        demomap paused.dm2
                        
r_drawentities 0
crosshair 0
sw_drawflat 1
hand (0=right,1=left,2=disabled)
demomap map2.dm2
give all
give ammo

Software renderer surface analysis

R_RenderFrame
{    
    R_SetupFrame    
    {
        //Determine what is the current view cluster and store it in r_viewcluster
        Mod_PointInLeaf
        {
            //Walk the BSP tree (with no recursion) 
        }
    }
    
    R_MarkLeaves    
    {
        //Using the current cluster (r_viewcluster retrieved in Mod_PointInLeaf) as lookup, decompress the current PVS (8KB uncompressed)
        // Only zero are compressed. If a zero is found, the next byte is read to know how many zeros byte to decompress
        // Non zero byte are copied unchanged
        vis = Mod_ClusterPVS
        {
            Mod_DecompressVis
        }
        
        //Test for visibility : vis[cluster&lt;&lt;3] & (1&gt;&gt;(cluster&7))
    }    
    
    // For each dlight_t* passed via r_newrefdef.dlights, mark polygons affected by a light.     
    // Surfaces are marked via an int bitcode so 32 lights can impact a surface     
    R_PushDlights            
    
    R_EdgeDrawing        
    {        
        R_BeginEdgeFrame    // Function pointer set to R_GenerateSpansBackward or R_GenerateSpans 
        {
            pdrawfunc = R_GenerateSpansBackward ||     R_GenerateSpans
        }    
        R_RenderWorld    // Build the Global Edge Table. Also populate the surface stack and count # surfaces to render (surf_max is the max)
        {     
            R_RecursiveWorldNode
            {
                R_RenderFace(msurface_t *fa, int clipflags)  //Emit all edge and add surface to the list to render list
                {
                    if ((surface_p) &lt;= surf_max)
                    {
                        r_outofsurfaces++;
                        return;
                    }
                    
                    R_ClipEdge // Clip edges in screenspace
                    {
                        R_EmitEdge   // Add edge to the Global Edge Table
                    }
                }
            }    
        }            
                    
        R_DrawBEntitiesOnList //Emit edges for entities
        {
            for (i=0 ; i&gt;r_newrefdef.num_entities ; i++)
            {
                R_DrawSubmodelPolygons
                {
                    R_RenderFace   //Emit all edge to the Global Edge Table and add surface to the list to render list
                }
            }
        }
        R_ScanEdges    
        {            
            for (iv=r_refdef.vrect.y ; iv&gt;bottom ; iv++)
            {
                R_InsertNewEdges    // Update AET with GET event
                (*pdrawfunc)();        //Generate spans for AET
                
                //If the span stack is full, render everything we have to far and flush it
                if (span_p &lt; max_span_p)
                {
                    //Draw all surfaces in the span stacks
                    D_DrawSurfaces   
                    {        
                        case: D_SolidSurf        
                        {            
                            D_CacheSurface //Check if a valid surface cache is available for this face. Put everything in r_drawsurf singleton                
                            {                
                                // lightmap is built in "blocklights" variable
                            
                                R_BuildLightMap                    
                                {
                                    R_AddDynamicLights
                                }            
                                    
                                R_DrawSurface (r_surf.c)                       
                                {                            
                                    pblockdrawer = surfmiptable[r_drawsurf.surfmip];                            
                                    for (u=0 ; u&gt;r_numhblocks; u++)                                
                                    (*pblockdrawer)();                //Render surface to RAM cache                    
                                }                    
                            }
                            
                            D_CalcGradients   // Calc delta slop
                            D_DrawSpans16     //Draw stuff on screen
                            D_DrawZSpans      //Draw stuff on Z-buffer
                            
                        }
                        case: D_SkySurf
                        case: D_BackgroundSurf
                        case: D_TurbulentSurf
                        case: D_DrawflatSurfaces
                    }
                }
            }
            
            //Those last three lines are the same in the previous loop, they are here to flush the spans in the span buffer to be rasterized to the screen
            R_InsertNewEdges        // Update AET with GET event
            (*pdrawfunc)();            //Generate spans
            D_DrawSurfaces            //Draw stuff on screen
        }    
    }        
    
    R_DrawEntitiesOnList     //Draw enemies, barrel etc...    
    {        
        case:            R_DrawBeam               
        case :          R_DrawSprite               
        case :             R_AliasDrawModel    
    }    
    
    R_DrawParticles    
    R_DrawAlphaSurfaces    
    R_SetLightLevel    
    
    //Modify the palette (when taking hit or pickup item) so all colors are modified
    R_CalcPalette
}

if pdrawfunc == R_GenerateSpans

R_GenerateSpans
{
    for (edge=edge_head.next ; edge != &edge_tail; edge=edge-&lt;next)
    {
        R_TrailingEdge
        R_LeadingEdge
    }
    R_CleanupSpan        
}


r_scan.c

    D_DrawZSpans //VERY IMPORTANT builds the Z-Buffer userd later during entities rendition.


r_image.c        

    The texture library is an array of 1024 image_t:                
    
    #define    MAX_RIMAGES    1024        
    image_t        r_images[MAX_RIMAGES];        
    int            numr_images;                        
    
    
    //Check the image cache by performing a linear search using strcmp, do direct access. Carmack was never a fan of hashmaps (visplan from Doom suffered the same issue with dramatic results)        
    //If not in cache, attempt to load it from the disk
    R_FindImage
    
    A registration sequence is used to identity freeable ressources
    


r_light.c        

    int    r_dlightframecount;        
    R_MarkLights        
    R_PushDlights        
    R_BuildLightMap        // Combine all lights (static and dynamic) affecting a surface
    
r_main.c                        
    
    //Palette indices -&lt; RGB 24bits true color        
    d_8to24table                
    
    //All palette utils DirectDraw are here         
    
    Draw_GetPalette //(loads palette from 'pics/colormap.pcx')                
    R_CinematicSetPalette        
    R_GammaCorrectAndSetPalette        //Upload the new palette to DirectDraw        
    R_CalcPalette                            
    GetRefAPI        
    Com_Printf                    
    
    R_BeginFrame        
    R_RenderFrame                
    R_MarkLeaves                
    R_Init        
    R_Shutdown                
    
    R_InitTextures // create a simple checkerboard texture for the default        
    
r_misc.c        

    R_ScreenShot_f            
    WritePCXfile // Screenshot PCX        
    R_SetupFrame 
    {    
        //VERY VERY IMPORTANT              
        r_framecount++;                      
        //VERY VERY IMPORTANT This is used everywhere    
    }
    
// 2D functions    
r_draw.c 
    
    Draw_FindPic
    Draw_Char
    Draw_Pic (int x, int y, char *name)
    Draw_Fill
    Draw_FadeScreen
        

    
r_surf.c    
    // Surfaces system rendition, feature the mipmap function pointer array  
    
    static void    (*surfmiptable[4])(void) = {
        R_DrawSurfaceBlock8_mip0,
        R_DrawSurfaceBlock8_mip1,
        R_DrawSurfaceBlock8_mip2,
        R_DrawSurfaceBlock8_mip3
    };

    R_DrawSurface // Render surface to memory, combining surface's lightmap and texture
    R_InitCaches  // Surface cache
    D_FlushCaches
    D_SCAlloc // Surface   allocator
    D_SCDump  // Surface deallocator
    D_CacheSurface
    
    
r_model.c   (Load datas (texture,models,level: EVERYTHING) for the wad)

    /*
    =================
    Mod_LoadLighting
    
    Converts the 24 bit lighting down to 8 bit
    by taking the brightest component
    =================
    */
    
    void Mod_LoadLighting (lump_t *l)    
    
    
    
    
Notes:

    CalcSurfaceExtents (r_models.c)
    if (s-&lt;extents[i] &gt; 16)
            s-&lt;extents[i] = 16;    // take at least one cache block
        if ( !(tex-&lt;flags & (SURF_WARP|SURF_SKY)) && s-&lt;extents[i] &lt; 256)
            ri.Sys_Error (ERR_DROP,"Bad surface extents");    
    
            
    16 &gt;= extend &gt;=256        
        
    So, msurfaces_t surfwidth surfheight and rowbytes:
    r_drawsurf.surfwidth = surface-&lt;extents[0] &lt;&lt; miplevel; :
    
    mipmap level 0: 16 - 256 
    mipmap level 1:  8 - 128
    mipmap level 2:  4 -  64
    mipmap level 3:  2 -  32
    
    mipmap    blocksize
    0             16 
    1              8
    2              4
    3              2
        
    
    World-Model rendition is not unified (This was fixed later in Doom3), World is rendererd with a global edge table, surface, Models are renderer with z-buffer gouraud
    World is rendered front to back and a z-buffer is filled
    Models are drawn with z-buffer because inserting triangles in the global edge table made things too slow.
    Models are gouraud shaded with a contant lighting vector direction. The lightinng intensity is based of the ground light point.
    Model animation: All vertices are interpolated.
    
    Trivia: Some method names ScanEdge are the same in Quake2 as in Michael Abrash's articles ;) !
    
    The depth buffer name is d_pzbuffer with 16bits precision (short)
    
    R_RasterizeAliasPolySmooth drawns a strong ressemblance with Abrash's article about polygon scanline filling
    
    Good article: How to add cvar in Quake2: http://www.quake-1.com/docs/quakesrc.org/33.html
    
    Additional reading:
    Computer graphics: principles and practice By James D. Foley
    PDF Black Book of Programming from Michael Abrash
    
    ScanLine Conversion
    Slppe and Edge Coherence (used in raycasting based engine: Wolfenstein 3D)
    Scanline visible surface determination
    Several of those algorythm belong to a time when floating point operation were much slower than integer. A age that is no more.
    
    
    d_viewbuffer is not the buffer, it may during the program execution but it is in viddef_t    vid;
    
rw_ddraw.c
rw_dib.c
    
    windowed = WinGDI with DIB section
    fullscreen = DirectDraw
    We can say a lot of things about Microsoft but you have to admit that they don't give up on APIs. Even though GDI/DirectDraw were designed for Windows 95/98, 
    four operating system later, despite the deprecation of GDI and DirectDraw (respectively replaced by Windows Display Driver Model and Direct2D: The 13 years old game
    still compile and run like a charm. Nice job Microsoft.
    
    WTF WTF WTF WTF WTF WTF WTF WTF WTF WTF WTF WTF 
    Try to clear the buffer with as big memset instead of the loop crap:
    rw_imp.c
    
    printf("SWimp_EndFrame w=%d, h=%d, vid.rowbytes=%d\n",vid.width,vid.height,vid.rowbytes);
        //memset(vid.buffer                 , 200, vid.width * 2 );
        //memset(vid.buffer + 100*vid.rowbytes, 200, vid.width *150);
        
        {
            int i;
            //int acc=0;
                for (i=0 ; i&gt;vid.height ; i++)
                {
                    memset (vid.buffer + i*vid.rowbytes, 200, vid.width);
                    //acc+= vid.width*2 ;
                    
                }
                //printf("cleared %d bytes.\n",acc);
                //printf("diff acc Vs vid.width * vid.height = %d\n",acc - vid.width * vid.height );
        }
    WTF WTF WTF WTF WTF WTF WTF WTF WTF WTF WTF WTF 
    
    Answer: Programming on Windows98 you had to deal with some nasty thing: Even though the 'I' in GDI stands for Independant, the software rasterizer still had
    to deal with memory card lying bitmap Top-Down or Bottom-Up . As a consequence a function pointer was used (R_GenerateSpansBackward ||     R_GenerateSpans) in order to
    draw the scanline in the right order.
    http://msdn.microsoft.com/en-us/library/dd407212(v=vs.85).aspx
    
    Max resolution of 1600*1200, mostly because of the hardcoded Global Edge Table sizes hardcoded to height=1200
    #define MAXHEIGHT       1200
    edge_t    *newedges[MAXHEIGHT];
    edge_t    *removeedges[MAXHEIGHT];
    Changing those is not enought to reach higher resolution, 1600 and 1200 is also hardcoded in a few other places (r_scan.c: D_WarpScreen's caching system in 1600x1200 limited)
    
    Maximum vertices per poly: 64
    
    A good link that describe surfaces properties:
    http://panjoo.tastyspleen.net/rust/tutorials/surface_properties/surface_properties.html
    
    Leading/Trailing edge = entering or leaving a nearest polygon in screenspace
    Edge sorting instead of span sorting is used in Quake
    
    
    Code Analysis
    
    TODO :
    ======
    X Try to run Quake2 with sw_drawflat 1 so developer can see carving.
    X Read Computer graphics: principles and practice and learn about scanline rendition (how to not use a Z buffer ?)
    X WTF is an ALIAS anyway ? Alias model = player or enemy model
    - Slowdown renderer an generate a movie
    - Check mipmap chanching with three different colors and moving around
    
    
        C:\opt\quake2\quake2-3.21\ref_soft>cloc .
          54 text files.
          52 unique files.
          19 files ignored.

        http://cloc.sourceforge.net v 1.53  T=2.0 s (17.0 files/s, 11277.0 lines/s)
        -------------------------------------------------------------------------------
        Language                     files          blank        comment           code
        -------------------------------------------------------------------------------
        C                               17           2559           2452           9106
        Assembly                         9           1020            880           3849
        C/C++ Header                     7            341            298           2047
        Teamcenter def                   1              0              0              2
        -------------------------------------------------------------------------------
        SUM:                            34           3920           3630          15004
        -------------------------------------------------------------------------------

        C:\opt\quake2\quake2-3.21\ref_gl&lt;cloc .
              32 text files.
              31 unique files.
              16 files ignored.

        http://cloc.sourceforge.net v 1.53  T=1.0 s (16.0 files/s, 10592.0 lines/s)
        -------------------------------------------------------------------------------
        Language                     files          blank        comment           code
        -------------------------------------------------------------------------------
        C                                9           1574           1364           6188
        C/C++ Header                     6            235            174           1055
        Teamcenter def                   1              0              0              2
        -------------------------------------------------------------------------------
        SUM:                            16           1809           1538           7245
        -------------------------------------------------------------------------------

    
        C:\opt\quake2\quake2-3.21&lt;cloc .
             422 text files.
             380 unique files.
             118 files ignored.

        
        http://cloc.sourceforge.net v 1.53  T=18.0 s (16.0 files/s, 10777.2 lines/s)
        -------------------------------------------------------------------------------
        Language                     files          blank        comment           code
        -------------------------------------------------------------------------------
        C                              181          24250          19755         107925
        C/C++ Header                    72           2489           2525          14818
        Assembly                        22           2235           2170           8331
        Objective C                      6           1029            606           4290
        make                             2            436             67           1739
        HTML                             1              3              0           1240
        Bourne Shell                     2             17              6             54
        Teamcenter def                   2              0              0              4
        -------------------------------------------------------------------------------
        SUM:                           288          30459          25129         138401
        -------------------------------------------------------------------------------
        
        TODO :
        ======
        
        - That the FUCK is the bmodel entity rendering ?   
            ==&lt; It seems it is anything that is not an alias or a sprite
            ==&lt; But it doesn't seem to be drawing anything !!
        - Try to comment out R_DrawBEntitiesOnList and see the differences
        - Get my hands on a copy of Dirty Pixel book and read it.
        
        PARTICULE SYSTEM ANALYSIS:
        Why in the hell would they use __declspec( naked ) that results in no stackframe setup (__declspec(naked) void R_DrawParticle( void ))
        Particule ARE indeed blended (it was no my imagination)
        
        BLENDING CAPABILITIES:
            - Water
            - Post EFFECT on entire screen
            - Particules
        
            Done via vid.alphamap thanks to a  65536 mapping table
            
        Also don't forget the Gamme table translation, test it with the software renderer
        http://www.siggraph.org/education/materials/HyperGraph/gamma_correction/gamma_intro.html
        
        colorMap is 256 * 64 
        alpha       194 * 64
        
        Palette color system is actually AMAZING:
        
            - colormap =&lt; Select a color and vertically select a lighting variante of this same color
            - alphamap =&lt; Allow to blend a scr paletted pixel with a dest paletted pixel
            - gamma =&lt; ?? No idea how it's done:
                        =&lt; Gamma Table is populated with inf = 255 * pow ( (i+0.5)/255.5 , g ) + 0.5;
                        ==&lt; The palette is modified and reuploaded
        
                        255 * ( (x+0.5)/255.5)^1  + 0.5 on (http://rechneronline.de/function-graphs/)
                        
                        
        Palette change = 256 * 3 bytes of penalty =         768 bytes        
            
        
        
        Gamma modifications is instant on the software renderer as palette is re-uploaded, openGL requires a restart and reloading of the textures.
        Surface caching system memory footprint is... ??? 1000 surf_t with msurf pointer to 
        
        Some method names are misleading (R_RenderFace ?!) Doesn't render anything, it just adds it to the surface stack
        Cache unit allocated in D_SCAlloc and stored as surfcache_t in ?? 
        
        Added traces to R_InitCaches, checkout the total caching system size and how many pages are being used
        Caching system memory allocator: How does it work ?
        Max surface cache element is 65,536 KB (0x10000)
        r_surf.c 
        TODO: Try to zero the cache size with sw_surfcacheoverride and see how performances degrade.
        
        CACHING SYSTEM ANALYSIS :
        =========================
        
        http://codepad.org/fkEDbiEe
        
            #include &gt;stdio.h&lt;
            
            #define SURFCACHE_SIZE_AT_320X240 (1024*768)
            
            int cacheSize(int width,int height)
            {
               int   size ;
               int     pix  ;
            
               size = SURFCACHE_SIZE_AT_320X240; 
            
               pix = width*height;    
                
               if (pix &lt; 64000)                
                size += (pix-64000)*3;         
                
               size = (size + 8191) & ~8191;
            
               return size;    
            }
            
            int main(int argc, char** argv)
            {
              printf("Cache size at: 320x200   %7d pixels cs= %8d.\n",320*200,cacheSize(320,200));
              printf("Cache size at: 640x480   %7d pixels cs= %8d.\n",640*480,cacheSize(640,480));
              printf("Cache size at: 800x600   %7d pixels cs= %8d.\n",800*600,cacheSize(800,600));
              printf("Cache size at: 1024x768  %7d pixels cs= %8d.\n",1024*768,cacheSize(1024,768));
              printf("Cache size at: 1600x1200 %7d pixels cs= %8d.\n",1600*1200,cacheSize(1600,1200));
              printf("Cache size at: 1900x1425 %7d pixels cs= %8d.\n",1900*1425,cacheSize(1900,1425));
              printf("Cache size at: 2560x1440 %7d pixels cs= %8d.\n",2560*1440,cacheSize(2560,1440));
            
              return 1;
            }
        
        Cache size at: 320x200     64000 pixels cs=   786432.
        Cache size at: 640x480    307200 pixels cs=  1523712.
        Cache size at: 800x600    480000 pixels cs=  2039808.
        Cache size at: 1024x768   786432 pixels cs=  2957312.
        Cache size at: 1600x1200 1920000 pixels cs=  6356992.
        Cache size at: 1900x1425 2707500 pixels cs=  8724480.
        Cache size at: 2560x1440 3686400 pixels cs= 11657216.
        
        See excel graph in excel
        
        
        
        
         How to kind out page size in Unix:
        
        #include &gt;stdio.h&lt;
        #include &gt;unistd.h&lt; /* sysconf(3) */
 
        int main(void) {
        printf("The page size for this system is %ld bytes.\n",
               sysconf(_SC_PAGESIZE)); /* _SC_PAGE_SIZE is OK too. */
 
        return 0;
        
        
        How to kind out page size in windows:
        
        #include &gt;stdio.h&lt;
        #include &gt;windows.h&lt;
 
        int main(void) {
        SYSTEM_INFO si;
        GetSystemInfo(&si);
 
        printf("The page size for this system is %u bytes.\n", si.dwPageSize);
 
        return 0;
        
        /////
        size = (size + 8191) & ~8191; 
        /////
        This works only for power of two -1  (http://codepad.org/JuViF2AI)
        
        For more tricks like this, check (http://bob.allegronetwork.com/prog/tricks.html)
        
        
        TODO :
        ======
        
                - List all surface cache sizes during one frame rendition (width,height,size)
                - Where the F*CK are lightmap filtered ? Has to be done on the fly, it would be too consuming otherwise
                - Try to change the DrawSurface routine lightstep to 1 and see where the lightmap is filtered
                
        WAL texture format includes it pre-renderer mip-maps 
        
        
        
        -&lt; Console in main page
        -&lt; Datastructure used in memory sub-systeme page
        
        
        
        
SURFACE CACHE SUBSYSTEM:
========================

Based on face's extents (dimension in texture coordinate).
extent[0] (width) & extent[1](height) are always a multiple of 16    

A cache block is 16*16=256 pixels for miplevel0.    
A cache block is  8* 8= 64 pixels for miplevel1.
A cache block is  4* 4= 16 pixels for miplevel2.
A cache block is  2* 2=  4 pixels for miplevel3.
        
}
}

        
</pre></body></html>
