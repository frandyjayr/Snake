#include "ResourceHolder.hpp"

/*****************************************************************************************************************
 *										loadTextures()   														 *
 *****************************************************************************************************************
 * Input: Textures::ID indicating textures name, std::string& indicating the file name							 *
 * Output: None																									 *
 * Description: The following loads textures into a std::map. It is a handy function to keep all textures in one *
 * data structure.																								 *
 ****************************************************************************************************************/
void ResourceHolder::loadTextures(Textures::ID id, const std::string& filename)
{
	std::unique_ptr<sf::Texture> texture(new sf::Texture());
	if (!texture->loadFromFile(filename))
	{
		std::cout << filename << " failed to load" << std::endl;
	}
	else
	{
		std::cout << filename << " SUCCESFULLY loaded!" << std::endl;
	}

	mTextureMap.insert(std::make_pair(id, std::move(texture)));
}

/*****************************************************************************************************************
 *										loadSoundBuffers()   													 *
 *****************************************************************************************************************
 * Input: soundBuffers::ID indicating soundBuffer name, std::string& indicating the file name					 *
 * Output: None																									 *
 * Description: The following loads soundBuffers into a std::map. It is a handy function to keep all soundBuffers* 
 * in one data structure.																						 *
 ****************************************************************************************************************/
void ResourceHolder::loadSoundBuffers(SoundBuffers::ID id, const std::string& filename)
{
	std::unique_ptr<sf::SoundBuffer> sound(new sf::SoundBuffer());
	
	if (!sound->loadFromFile(filename))
	{
		std::cout << filename << " failed to load" << std::endl;
	}
	else
	{
		std::cout << filename << " SUCCESFULLY loaded!" << std::endl;
	}

	mSoundBufferMap.insert(std::make_pair(id, std::move(sound)));
	
}

/*****************************************************************************************************************
 *										loadMusic()   														     *
 *****************************************************************************************************************
 * Input: Music::ID indicating music name, std::string& indicating the file name							     *
 * Output: None																									 *
 * Description: The following music textures into a std::map. It is a handy function to keep all music in one    *
 * data structure.																								 *
 ****************************************************************************************************************/
void ResourceHolder::loadMusic(Music::ID id, const std::string& filename)
{
	std::unique_ptr<sf::Music> music(new sf::Music());

	if (!music->openFromFile(filename))
	{
		std::cout << filename << " failed to load" << std::endl;
	}
	else
	{
		std::cout << filename << " SUCCESFULLY loaded!" << std::endl;
	}

	mMusicMap.insert(std::make_pair(id, std::move(music)));

}

/*****************************************************************************************************************
 *										loadFont()   														     *
 *****************************************************************************************************************
 * Input: Font::ID indicating font name, std::string& indicating the file name							         *
 * Output: None																									 *
 * Description: The following loads fonts into a std::map. It is a handy function to keep all fonts in one	     *
 * data structure.																								 *
 ****************************************************************************************************************/
void ResourceHolder::loadFonts(Fonts::ID id, const std::string& filename)
{
	std::unique_ptr<sf::Font> font(new sf::Font());
	if (!font->loadFromFile(filename))
	{
		std::cout << filename << " failed to load" << std::endl;
	}
	else
	{
		std::cout << filename << " SUCCESFULLY loaded!" << std::endl;
	}

	mFontMap.insert(std::make_pair(id, std::move(font)));
}

/*****************************************************************************************************************
 *										getTextures()   														 *
 *****************************************************************************************************************
 * Input: Textures::ID indicating font name																		 *
 * Output: None																									 *
 * Description: The following function retrieves textures from the map that were stored using the respective     *
 * load function.																								 *
 ****************************************************************************************************************/
sf::Texture& ResourceHolder::getTextures(Textures::ID id)
{
	auto found = mTextureMap.find(id);
	return *found->second;
}

/*****************************************************************************************************************
 *										getSoundBuffers()   													 *
 *****************************************************************************************************************
 * Input: SoundBuffers::ID indicating font name																	 *
 * Output: None																									 *
 * Description: The following function retrieves soundBuffers from the map that were stored using the respective *
 * load function.																								 *
 ****************************************************************************************************************/
sf::SoundBuffer& ResourceHolder::getSoundBuffers(SoundBuffers::ID id)
{
	auto found = mSoundBufferMap.find(id);
	return *found->second;
}

/*****************************************************************************************************************
 *										getMusic()   														     *
 *****************************************************************************************************************
 * Input: Music::ID indicating font name																		 *
 * Output: None																									 *
 * Description: The following function retrieves Music from the map that were stored using the respective        *
 * load function.																								 *
 ****************************************************************************************************************/
sf::Music& ResourceHolder::getMusic(Music::ID id)
{
	auto found = mMusicMap.find(id);
	return *found->second;
}

/*****************************************************************************************************************
 *										getFont()   									   					     *
 *****************************************************************************************************************
 * Input: Font::ID indicating font name																		     *
 * Output: None																									 *
 * Description: The following function retrieves fonts from the map that were stored using the respective        *
 * load function.																								 *
 ****************************************************************************************************************/
sf::Font& ResourceHolder::getFont(Fonts::ID id)
{
	auto found = mFontMap.find(id);
	return *found->second;
}