# KallistiOS 1.2.0
#
# gamepack/Makefile
# (c)2002-2005 Viktor Gars
#

include $(KOS_BASE)/Makefile.rules

COMMON_OBJS = ../dccommon/src/point.o ../dccommon/src/rect.o ../dccommon/src/gldraw.o ../dccommon/src/dccontrol.o ../dccommon/src/plprint.o ../dccommon/src/timer.o
FALLDOWN_OBJS = src/falldown/fd_ball.o src/falldown/fd_field.o src/falldown/fd_game.o src/falldown/fd_draw.o src/falldown/fd_control.o src/falldown/falldown.o
MINESWEEPER_OBJS = src/minesweeper/ms_tile.o src/minesweeper/ms_field.o src/minesweeper/ms_control.o src/minesweeper/ms_game.o src/minesweeper/ms_draw.o src/minesweeper/minesweeper.o
SIMON_OBJS = src/simon/s_control.o src/simon/s_game.o src/simon/s_draw.o src/simon/simon.o
STARTER_OBJS = src/starter/st_player.o src/starter/st_control.o src/starter/st_game.o src/starter/st_draw.o src/starter/starter.o
PONG_OBJS = src/pong/p_ball.o src/pong/p_control.o src/pong/p_game.o src/pong/p_draw.o src/pong/pong.o
SUDOKU_OBJS = src/sudoku/sd_control.o src/sudoku/sd_game.o src/sudoku/sd_draw.o src/sudoku/sudoku.o
MAIN_OBJS = src/main/draw.o src/main/game.o src/main/control.o src/main/player.o src/main/players.o src/main/gp_draw.o src/main/gamepack.o src/main.o

DATAOBJS = bin/romdisk.o

TARGET = bin/gamepack1.elf

KOS_LOCAL_CFLAGS = -D__DEBUG__ -I./include -I../dccommon/include -I$(KOS_BASE)/addons/zlib

all: romdisk falldown minesweeper simon starter pong main gamepack #dist

clean: cfalldown cminesweeper csimon cstarter cpong cmain
	-rm -f bin/falldown.elf
	-rm -f bin/romdisk.*
	-rm -f $(TARGET)

cpong:
	-rm -f $(PONG_OBJS)

cmain:
	-rm -f $(MAIN_OBJS)
	
csimon:
	-rm -f $(SIMON_OBJS)
	
cfalldown:
	-rm -f $(FALLDOWN_OBJS)
	
cstarter:
	-rm -f $(STARTER_OBJS)

cminesweeper:
	-rm -f $(MINESWEEPER_OBJS)

romdisk.img:
	$(KOS_GENROMFS) -f bin/romdisk.img -d romdisk -v

romdisk: romdisk.img
	$(KOS_BASE)/utils/bin2o/bin2o bin/romdisk.img romdisk bin/romdisk.o

gamepack: romdisk
	$(KOS_CCPLUS) $(KOS_CFLAGS) $(KOS_CPPFLAGS) $(KOS_LDFLAGS) -o $(TARGET) \
	$(KOS_START) $(MAIN_OBJS) $(FALLDOWN_OBJS) $(MINESWEEPER_OBJS) $(SIMON_OBJS) \
	$(PONG_OBJS) \
	$(STARTER_OBJS) $(COMMON_OBJS) $(DATAOBJS) $(OBJEXTRA) $(KOS_LIBS)\
	-lk++ -lgl -lpng -lbz2 -lz -ldcplib -lm -lkallisti -lgcc -lpcx $(KOS_LIBS)

main: $(MAIN_OBJS)

falldown: $(FALLDOWN_OBJS)

minesweeper: $(MINESWEEPER_OBJS)

simon: $(SIMON_OBJS)

starter: $(STARTER_OBJS)

pong: $(PONG_OBJS)

sudoku: $(SUDOKU_OBJS)

run:
	$(KOS_LOADER) $(TARGET)

dist:
	$(KOS_STRIP) $(TARGET)
