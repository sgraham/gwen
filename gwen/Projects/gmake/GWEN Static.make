# GNU Make project makefile autogenerated by Premake
ifndef config
  config=release
endif

ifndef verbose
  SILENT = @
endif

ifndef CC
  CC = gcc
endif

ifndef CXX
  CXX = g++
endif

ifndef AR
  AR = ar
endif

ifeq ($(config),release)
  OBJDIR     = obj/Release/GWEN\ Static
  TARGETDIR  = ../../lib/gmake
  TARGET     = $(TARGETDIR)/libgwen_static.a
  DEFINES   += -DNDEBUG -DGWEN_COMPILE_STATIC
  INCLUDES  += -I../../include
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -g -O2 -ffast-math
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -L../../lib -L../../lib/gmake
  LIBS      += 
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += 
  LINKCMD    = $(AR) -rcs $(TARGET) $(OBJECTS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),debug)
  OBJDIR     = obj/Debug/GWEN\ Static
  TARGETDIR  = ../../lib/gmake
  TARGET     = $(TARGETDIR)/libgwend_static.a
  DEFINES   += -D_DEBUG -DGWEN_COMPILE_STATIC
  INCLUDES  += -I../../include
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -g
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -L../../lib -L../../lib/gmake
  LIBS      += 
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += 
  LINKCMD    = $(AR) -rcs $(TARGET) $(OBJECTS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

OBJECTS := \
	$(OBJDIR)/Anim.o \
	$(OBJDIR)/BaseRender.o \
	$(OBJDIR)/DragAndDrop.o \
	$(OBJDIR)/events.o \
	$(OBJDIR)/Gwen.o \
	$(OBJDIR)/Hook.o \
	$(OBJDIR)/inputhandler.o \
	$(OBJDIR)/Skin.o \
	$(OBJDIR)/ToolTip.o \
	$(OBJDIR)/Utility.o \
	$(OBJDIR)/Base.o \
	$(OBJDIR)/Button.o \
	$(OBJDIR)/Canvas.o \
	$(OBJDIR)/CheckBox.o \
	$(OBJDIR)/ColorControls.o \
	$(OBJDIR)/ColorPicker.o \
	$(OBJDIR)/ComboBox.o \
	$(OBJDIR)/CrossSplitter.o \
	$(OBJDIR)/DockBase.o \
	$(OBJDIR)/DockedTabControl.o \
	$(OBJDIR)/Dragger.o \
	$(OBJDIR)/GroupBox.o \
	$(OBJDIR)/HorizontalScrollBar.o \
	$(OBJDIR)/HorizontalSlider.o \
	$(OBJDIR)/HSVColorPicker.o \
	$(OBJDIR)/ImagePanel.o \
	$(OBJDIR)/Label.o \
	$(OBJDIR)/LabelClickable.o \
	$(OBJDIR)/ListBox.o \
	$(OBJDIR)/Menu.o \
	$(OBJDIR)/MenuItem.o \
	$(OBJDIR)/MenuStrip.o \
	$(OBJDIR)/NumericUpDown.o \
	$(OBJDIR)/PanelListPanel.o \
	$(OBJDIR)/ProgressBar.o \
	$(OBJDIR)/Properties.o \
	$(OBJDIR)/RadioButton.o \
	$(OBJDIR)/RadioButtonController.o \
	$(OBJDIR)/ResizableControl.o \
	$(OBJDIR)/Resizer.o \
	$(OBJDIR)/RichLabel.o \
	$(OBJDIR)/ScrollBar.o \
	$(OBJDIR)/ScrollBarBar.o \
	$(OBJDIR)/ScrollBarButton.o \
	$(OBJDIR)/ScrollControl.o \
	$(OBJDIR)/Slider.o \
	$(OBJDIR)/SplitterBar.o \
	$(OBJDIR)/TabButton.o \
	$(OBJDIR)/TabControl.o \
	$(OBJDIR)/TabStrip.o \
	$(OBJDIR)/Text.o \
	$(OBJDIR)/TextBox.o \
	$(OBJDIR)/TextBoxNumeric.o \
	$(OBJDIR)/TreeControl.o \
	$(OBJDIR)/TreeNode.o \
	$(OBJDIR)/VerticalScrollBar.o \
	$(OBJDIR)/VerticalSlider.o \
	$(OBJDIR)/WindowControl.o \
	$(OBJDIR)/FileOpen.o \
	$(OBJDIR)/FileSave.o \
	$(OBJDIR)/Query.o \
	$(OBJDIR)/Null.o \
	$(OBJDIR)/Windows.o \

RESOURCES := \

SHELLTYPE := msdos
ifeq (,$(ComSpec)$(COMSPEC))
  SHELLTYPE := posix
endif
ifeq (/bin,$(findstring /bin,$(SHELL)))
  SHELLTYPE := posix
endif

.PHONY: clean prebuild prelink

all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

$(TARGET): $(GCH) $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking GWEN Static
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning GWEN Static
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild:
	$(PREBUILDCMDS)

prelink:
	$(PRELINKCMDS)

ifneq (,$(PCH))
$(GCH): $(PCH)
	@echo $(notdir $<)
	-$(SILENT) cp $< $(OBJDIR)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
endif

$(OBJDIR)/Anim.o: ../../src/Anim.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/BaseRender.o: ../../src/BaseRender.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/DragAndDrop.o: ../../src/DragAndDrop.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/events.o: ../../src/events.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Gwen.o: ../../src/Gwen.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Hook.o: ../../src/Hook.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/inputhandler.o: ../../src/inputhandler.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Skin.o: ../../src/Skin.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ToolTip.o: ../../src/ToolTip.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Utility.o: ../../src/Utility.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Base.o: ../../src/Controls/Base.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Button.o: ../../src/Controls/Button.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Canvas.o: ../../src/Controls/Canvas.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/CheckBox.o: ../../src/Controls/CheckBox.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ColorControls.o: ../../src/Controls/ColorControls.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ColorPicker.o: ../../src/Controls/ColorPicker.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ComboBox.o: ../../src/Controls/ComboBox.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/CrossSplitter.o: ../../src/Controls/CrossSplitter.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/DockBase.o: ../../src/Controls/DockBase.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/DockedTabControl.o: ../../src/Controls/DockedTabControl.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Dragger.o: ../../src/Controls/Dragger.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/GroupBox.o: ../../src/Controls/GroupBox.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/HorizontalScrollBar.o: ../../src/Controls/HorizontalScrollBar.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/HorizontalSlider.o: ../../src/Controls/HorizontalSlider.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/HSVColorPicker.o: ../../src/Controls/HSVColorPicker.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ImagePanel.o: ../../src/Controls/ImagePanel.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Label.o: ../../src/Controls/Label.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/LabelClickable.o: ../../src/Controls/LabelClickable.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ListBox.o: ../../src/Controls/ListBox.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Menu.o: ../../src/Controls/Menu.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/MenuItem.o: ../../src/Controls/MenuItem.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/MenuStrip.o: ../../src/Controls/MenuStrip.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/NumericUpDown.o: ../../src/Controls/NumericUpDown.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/PanelListPanel.o: ../../src/Controls/PanelListPanel.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ProgressBar.o: ../../src/Controls/ProgressBar.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Properties.o: ../../src/Controls/Properties.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/RadioButton.o: ../../src/Controls/RadioButton.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/RadioButtonController.o: ../../src/Controls/RadioButtonController.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ResizableControl.o: ../../src/Controls/ResizableControl.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Resizer.o: ../../src/Controls/Resizer.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/RichLabel.o: ../../src/Controls/RichLabel.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ScrollBar.o: ../../src/Controls/ScrollBar.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ScrollBarBar.o: ../../src/Controls/ScrollBarBar.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ScrollBarButton.o: ../../src/Controls/ScrollBarButton.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ScrollControl.o: ../../src/Controls/ScrollControl.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Slider.o: ../../src/Controls/Slider.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/SplitterBar.o: ../../src/Controls/SplitterBar.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/TabButton.o: ../../src/Controls/TabButton.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/TabControl.o: ../../src/Controls/TabControl.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/TabStrip.o: ../../src/Controls/TabStrip.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Text.o: ../../src/Controls/Text.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/TextBox.o: ../../src/Controls/TextBox.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/TextBoxNumeric.o: ../../src/Controls/TextBoxNumeric.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/TreeControl.o: ../../src/Controls/TreeControl.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/TreeNode.o: ../../src/Controls/TreeNode.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/VerticalScrollBar.o: ../../src/Controls/VerticalScrollBar.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/VerticalSlider.o: ../../src/Controls/VerticalSlider.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/WindowControl.o: ../../src/Controls/WindowControl.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/FileOpen.o: ../../src/Controls/Dialog/FileOpen.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/FileSave.o: ../../src/Controls/Dialog/FileSave.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Query.o: ../../src/Controls/Dialog/Query.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Null.o: ../../src/Platforms/Null.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Windows.o: ../../src/Platforms/Windows.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
