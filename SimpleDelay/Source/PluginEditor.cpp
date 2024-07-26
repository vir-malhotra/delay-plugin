/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleDelayAudioProcessorEditor::SimpleDelayAudioProcessorEditor (SimpleDelayAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
    gainAttachment (p.state, "gain", gainSlider),
    feedbackAttachment (p.state, "feedback", feedbackSlider),
    mixAttachment (p.state, "mix", mixSlider)
{
    gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    feedbackSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    mixSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);

    for (auto* slider : { &gainSlider, &feedbackSlider, &mixSlider }) {
        slider->setTextBoxStyle(juce::Slider::TextBoxBelow, true, 200, 30);
        addAndMakeVisible(slider);
    }
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

SimpleDelayAudioProcessorEditor::~SimpleDelayAudioProcessorEditor()
{
}

//==============================================================================
void SimpleDelayAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colour(0xff121212));

    g.setColour (juce::Colours::black);
    juce::Rectangle<float> backgroundRect = getLocalBounds().toFloat();
    int numBackgroundRects = 60;
    juce::Point<float> offset = backgroundRect.getBottomRight() / numBackgroundRects;

    for (int i = 0; i < numBackgroundRects; ++i) {
        g.drawRect(backgroundRect);
        backgroundRect += offset;
    }

    juce::Rectangle<int> bounds = getLocalBounds();
    juce::Rectangle<int> textArea = bounds.removeFromLeft((bounds.getWidth() * 2) / 3).removeFromBottom(bounds.getHeight() / 2).reduced(10);

    juce::ColourGradient gradient(juce::Colour(0xffe62875),
        textArea.toFloat().getTopLeft(), juce::Colour(0xffe43d1b), textArea.toFloat().getTopRight(), false);

    g.setGradientFill(gradient);

    g.setFont(textArea.toFloat().getHeight());
    g.drawFittedText("DEL", textArea, juce::Justification::centred, 1);
}

void SimpleDelayAudioProcessorEditor::resized()
{
    juce::Rectangle<int> bounds = getLocalBounds();
    int margin = 20;

    juce::Rectangle<int> gainBounds = bounds.removeFromRight(getWidth() / 3);
    gainSlider.setBounds(gainBounds.reduced(margin));
    juce::Rectangle<int> knobsBounds = bounds.removeFromTop(getHeight() / 2);
    juce::Rectangle<int> feedbackBounds = knobsBounds.removeFromLeft(knobsBounds.getWidth() / 2);
    feedbackSlider.setBounds(feedbackBounds.reduced(margin));
    mixSlider.setBounds(knobsBounds.reduced(margin));
    
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
