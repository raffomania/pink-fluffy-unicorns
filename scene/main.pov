#version 3.7;

#declare RandomSeed = seed(1337);

#declare Beat1_Start = 33.96;
#declare Beat1_Period = 28.14;

#declare BGSynths_Start = 2426;
#declare BGSynths_Period = 21.18; // frames

#declare Beat2_Start = 4952;
#declare Beat2_Period = 28.14; // frames

#declare start_part1_fade = 0;
#declare end_part1_fade = 800;
#declare start_break_down_fade = 1800;
#declare end_break_down_fade = 2400;
#declare start_focus_break_down = 3000;
#declare end_focus_break_down = 3800;
#declare start_part2_fade = 4920;
#declare end_part2_fade = 4951;
#declare end_song = 12724;
#declare fade_out_start = 9462;
#declare fade_out_end = 9840;

#macro Beat1()
    mod((clock + Beat1_Start) * 10000, Beat1_Period * 10000) / (Beat1_Period * 10000)
#end

#macro BGSynths()
    mod((clock + BGSynths_Start) * 10000, BGSynths_Period * 10000) / (BGSynths_Period * 10000)
#end

#macro BGSynths_2()
    mod((clock + BGSynths_Start) * 10000, BGSynths_Period * 2 * 10000) / (BGSynths_Period * 2 * 10000)
#end

#macro Beat2()
    mod((clock + Beat2_Start) * 10000, Beat2_Period * 10000) / (Beat2_Period * 10000)
#end

#include "colors.inc"
#include "shapes.inc"
#include "textures.inc"
#include "glass.inc"
#include "metals.inc"
#include "golds.inc"

#include "rad_def.inc"
#include "rand.inc"

#include "scene/camera.inc"

global_settings { assumed_gamma 2.2 }
global_settings { ambient_light rgb<1, 1, 1> }

#switch (clock)
    #range (start_part1_fade, start_break_down_fade)
        #include "scene/starfield.inc"
    #break
    #range (start_part2_fade, end_song)
        #include "scene/starfield.inc"
    #break
#end

#switch (clock)
    #range (end_part1_fade, start_break_down_fade)
        #include "scene/title.inc"
    #break
#end

// Funky sky include
#switch (clock)
    #range (start_break_down_fade, start_part2_fade)
        #include "scene/funky-sky.inc"
    #break
#end

#switch (clock)
    #range (start_break_down_fade, end_song)
        #include "scene/ship.inc"
    #break
#end

fog {
    #switch (clock)
        // Part1 fade-in
        #range (start_part1_fade, end_part1_fade)
            distance Interpolate(clock, start_part1_fade, end_part1_fade, 0.01, 100, 1)
        #break

        // Part1
        #range (end_part1_fade, start_break_down_fade)
            distance 100
        #break

        // Break down
        #range (start_break_down_fade, end_break_down_fade)
            distance Interpolate(clock, start_break_down_fade, end_break_down_fade, 0.01, 100, 1)
            #local shade = Interpolate(clock, start_break_down_fade, end_break_down_fade, White, Black, 1);
            #local trans = Interpolate(clock, start_break_down_fade, end_break_down_fade, 0, 1, 1);
            color rgbt<shade.red, shade.blue, shade.green, trans>
        #break

        // Part2 fade-in
        #range (start_part2_fade, end_part2_fade)
            distance 0.1
        #break

        // Part2
        #range (end_part2_fade, fade_out_start)
            distance 100
        #break

        // Fade-out
        #range (fade_out_start, fade_out_end)
            distance Interpolate(clock, fade_out_start, fade_out_end, 100, 0.01, 1)
        #break
    #end
}
