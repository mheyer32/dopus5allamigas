/*

Directory Opus 5
Original APL release version 5.82
Copyright 1993-2012 Jonathan Potter & GP Software

This program is free software; you can redistribute it and/or
modify it under the terms of the AROS Public License version 1.1.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
AROS Public License for more details.

The release of Directory Opus 5 under the GPL in NO WAY affects
the existing commercial status of Directory Opus for Windows.

For more information on Directory Opus for Windows please see:

                 http://www.gpsoft.com.au

*/

char *strings[] =
{
    // THANK
    "You're welcome",
    "I'm glad I could help",

	// OPUS
	"Directory Opus is a great program isn't it!",
	"GPSoftware sure came up with a winner with Opus, didn't they?",
	"Directory Opus makes the Amiga so much more powerful!",
	"You'll be upgrading to the next version of Opus soon, won't you?",
	"I love Directory Opus!",
	"Who needs sex with Directory Opus around?",

	// Naughties
	"That's a bit rude isn't it?",
	"There's no need for language like that!",
	"Mind your manners please!",
	"How dare you use language like that in front of a lady?",

    // CAN YOU
    "Don't you believe that I can*",
    "Perhaps you believe I should*",
    "You want me to be able to*",

    // CAN I
    "Perhaps you don't want to*",
    "Do you want to be able to*",

    // YOU ARE, YOU'RE
    "What makes you think I am*",
    "Does it please you to believe I am*",
    "Perhaps you would like to be*",
    "Do you sometimes wish you were*",

    // I DON'T
    "Don't you really*",
    "Why don't you*",
    "Do you want to be able to*",
    "Does it trouble you to not*",

    // I FEEL
    "Do you often feel*",
    "Why do you think you feel*",
    "Do you enjoy feeling*",

    // WHY DON'T YOU
    "Do you really believe I don't*",
    "Perhaps in good time I will*",
    "Do you want me to*",

    // WHY CAN'T I
    "Do you think you should be able to*",
    "Why can't you*",

    // ARE YOU
    "Why are you interested in whether or not I am*",
    "Would you prefer if I were not*",
    "Perhaps in your fantasies I am*",

    // I CAN'T
    "How do you know you can't*",
    "Have you tried?",
    "Perhaps you can now*",

    // I AM, I'M
    "Did you come to me because you are*",
    "How long have you been*",
    "Do you believe it is normal to be*",
    "Do you enjoy being*",

    // YOUR
    "Why are you concerned about my*",
    "What about your own*",

    // I WANT
    "What would it mean to you if you got*",
    "Why do you want*",
    "Suppose you soon got*",
    "What if you never got*",
    "I sometimes also want*",

    // HOW, WHO, WHERE, WHEN, WHY
    "Why do you ask?",
    "Does that question interest you?",
    "What answer would please you the most?",
    "What do you think?",
    "Are such questions on your mind often?",
    "What is it that you really want to know?",
    "Have you asked anyone else?",
    "Have you asked such questions before?",
    "What else comes to mind when you ask that?",

    // NAME
    "Names don't interest me.",
    "I don't care about names --please go on.",

    // CAUSE
    "Is that the real reason?",
    "Don't any other reasons come to mind?",
    "Does that reason explain anything else?",
    "What other reasons might there be?",

    // SORRY
    "Please don't apologize!",
    "Apologies are not necessary.",
    "What feelings do you have when you apologize?",
    "Don't be so defensive!",

    // DREAM
    "What does that dream suggest to you?",
    "Do you dream often?",
    "What persons appear in your dreams?",
    "Are you disturbed by your dreams?",

    // HELLO, HI
    "How do you do ...please state your problem.",

    // MAYBE
    "You don't seem quite certain.",
    "Why the uncertain tone?",
    "Can't you be more positive?",
    "You aren't sure?",
    "Don't you know?",

    // NO, NOT, NOTHING
    "Are you saying no just to be negative?",
    "You are being a bit negative.",
    "Why not?",
    "Are you sure?",
    "Why no?",

    // YOU
    "We were discussing you--not me.",
    "Oh, I*",
    "You're not really talking about me, are you?",

    // ALWAYS
    "Can you think of a specific example?",
    "When?",
    "What are you thinking of?",
    "Really, always?",

    // THINK
    "Do you really think so?",
    "But you are not sure*",
    "Do you doubt*",

    // ALIKE
    "In what way?",
    "What resemblance do you see?",
    "What does the similarity suggest to you?",
    "What other connections do you see?",
    "Could there really be some connection?",
    "How?",

    // YES
    "Are you sure?",
    "I see.",
    "I understand.",
    "You seem quite positive.",

    // FRIEND
    "Why do you bring up the topic of friends?",
    "Do your friends worry you?",
    "Do your friends pick on you?",
    "Are you sure you have any friends?",
    "Do you impose on your friends?",
    "Perhaps your love for friends worries you.",

    // COMPUTER
    "Do computers worry you?",
    "Are you talking about me in particular?",
    "Are you frightened by machines?",
    "Why do you mention computers?",
    "What do you think machines have to do with your problem?",
    "Don't you think computers can help people?",
    "What is it about machines that worries you?",

    // NOKEYFOUND
    "What does that suggest to you?",
    "I see.",
    "I'm not sure I understand you fully.",
    "Come come elucidate your thoughts.",
    "Can you elaborate on that?",
    "That is quite interesting.",
    "Say, do you have any psychological problems?",

	0
};


void main(void)
{
	short num;
	char *ptr;

	for (num=0;strings[num];num++)
	{
		printf("\t\"");
		for (ptr=strings[num];*ptr;ptr++)
			printf("\\x%x",(unsigned char)(~*ptr));
		printf("\",\n");
	}
}
