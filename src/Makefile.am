SUBDIRS = audiolib

bin_PROGRAMS = rott@SUFFIX@
rott@SUFFIX@_SOURCES = \
	byteorder.c \
	cin_actr.c \
	cin_efct.c \
	cin_evnt.c \
	cin_main.c \
	crc.c \
	dosutil.c \
	dukemusc.c \
	engine.c \
	hashtable.c \
	isr.c \
	modexlib.c \
	random.c \
	rt_actor.c \
	rt_battl.c \
	rt_build.c \
	rt_cfg.c \
	rt_com.c \
	rt_debug.c \
	rt_dmand.c \
	rt_door.c \
	rt_draw.c \
	rt_err.c \
	rt_floor.c \
	rt_game.c \
	rt_in.c \
	rt_main.c \
	rt_map.c \
	rt_menu.c \
	rt_msg.c \
	rt_net.c \
	rt_playr.c \
	rt_scale.c \
	rt_sound.c \
	rt_spbal.c \
	rt_sqrt.c \
	rt_stat.c \
	rt_state.c \
	rt_str.c \
	rt_swift.c \
	rt_ted.c \
	rt_util.c \
	rt_vid.c \
	rt_view.c \
	scriplib.c \
	w_wad.c \
	watcom.c \
	winrott.c \
	z_zone.c
rott@SUFFIX@_CFLAGS = @SDL2_CFLAGS@ @SDL2_mixer_CFLAGS@
rott@SUFFIX@_LDADD = audiolib/libaudiolib.a @SDL2_LIBS@ @SDL2_mixer_LIBS@
