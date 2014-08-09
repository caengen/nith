class Product < ActiveRecord::Base
	default_scope order: 'title'

	# Validations
	validates :title, uniqueness: true, length: { minimum: 10 }
	validates :title, :image_url, :description, presence: true
	validates :price, numericality: { greater_than_or_equal_to: 0.01 }
	validates :image_url, format: {
		with: %r{\.(gif|jpg|png)\z}i,
		message: 'must be a URL for GIF, JPG or PNG image.'
	}
end
