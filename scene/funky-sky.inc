#include "stars.inc"
#include "colors.inc"

#local rPosition = seed(6741);
#local V_Rotation = <RRand(-180,180,rPosition),RRand(-180,180,rPosition),RRand(-180,180,rPosition)>;


#macro Nebula(fSize, fEmission, rShapeSeed, rColor, beat)
   #if (fEmission = 0) #local fEmission=RRand(0.008,0.020,rColor); #end
   sphere { 0, 2 pigment { color rgbf<1, 1, 1,1> } finish { ambient 0.0 diffuse 0.0 }
      interior { media { intervals 10 samples 1, 5 confidence 0.9999 variance 1/1000 emission fEmission/fSize //0.008
         density { dents scale 0.2 
            turbulence 0.5+0.8*sin(beat*3.14159265359)
            octaves RRand(2,40,rShapeSeed)
            frequency RRand(1,2,rShapeSeed)
            lambda RRand(2.1,4.5,rShapeSeed)
            omega RRand(0.51,0.65,rShapeSeed)
            color_map { [0.0 rgb <0,0,0> transmit 1 ]
                        [0.8 color rgb <0,1,1> ]
                        [1.0 color rgb <1,0.5,0> ] }
         } 
      } }
      no_shadow
      scale 80*fSize
      hollow
   }
#end //macro

#macro StarField()
    #local STARFIELD_STAR_COLOR = rgb <0.9, 0.95, 1.0>;
    #local STARFIELD_STAR_INTENSITY = 1.0;
    bozo pigment_map { 
      [ 3.0 spotted color_map {
         [0.1 STARFIELD_STAR_COLOR*2*STARFIELD_STAR_INTENSITY ] // intensity 
         [0.3 rgb 0 transmit 1 ] // density
         } scale 1e-3
      ]
      [ 3.0 granite color_map {
         [0.70 rgb 0 transmit 1]
         [1.00 STARFIELD_STAR_COLOR ]
         } scale 1e-2
      ]
      [ 3.0 leopard color_map {
         [0.50 rgb 0 transmit 1 ] // density=0.5
         [1.00 STARFIELD_STAR_COLOR ]
         } scale 1e-5 ]
   }
#end


#switch (clock)
    #range (start_break_down_fade, BGSynths_Start)
        object {
            #local interpol = (clock-start_break_down_fade)/(BGSynths_Start-start_break_down_fade);
            Nebula(1, 0, seed(93265), seed(1825), interpol)
            rotate V_Rotation
            translate <0, 0, 120>
        }
        #break
    #range (BGSynths_Start, start_part2_fade)
        object {
            Nebula(1, 0, seed(93265), seed(1825), BGSynths())
            rotate V_Rotation
            translate <0, 0, 120>
        }
        #break
#end


sky_sphere { pigment { StarField() } }


sphere { 0, 1.5 pigment { color rgbf<1, 1, 1,1> } finish { ambient 0.0 diffuse 0.0 }
    interior {
        media {
            emission 0.02
            intervals 1
            samples 25
            method 3
            density {
                spherical
                ramp_wave
                translate 1.0*y
                warp { turbulence 2.5 }
                translate -1.0*y
                color_map {
                    [0.0 color rgb <0, 0, 0> * 0.5]
                    [0.1 color rgb <0, 1, 0> * 0.5]
                    [0.5 color rgb <1, 1, 0> * 0.5]
                    [1.0 color rgb <1, 0, 0> * 0.5]
                }
            }
            density {
                spherical
                ramp_wave
                color_map {
                    [0.0 color rgb 1]
                    [0.2 color rgb 1]
                    [0.3 color rgb 0]
                    [1.0 color rgb 0]
                }
            }
        }
    }
    scale 25
    hollow
    rotate <0, 180, 0>
}
