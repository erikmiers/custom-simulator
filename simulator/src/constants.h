/***************************************************************************
 * Copyright (C) 2020 by EWT                                               *
 *                                                                         *
 * All Rights Reserved.                                                    *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * Author: Erik Miers                                                      *
 * Email: erik.miers@gmail.com                                             *
 ***************************************************************************/

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QObject>


namespace Universe {


// Eulers number
constexpr double e = 2.7183;

// Density Constant (kg/m³)
constexpr double p = 3.86e22;

// Coulomb Constant (N)
constexpr double cc = 9e9;

// Planck length
constexpr double pl = 1e-35;




/**
 * @brief The Constants class a singleton providing "universal" constants
 */
class Constants : public QObject {
	Q_OBJECT

	// ----------------------------------------------------------------------
	//  X'truction
	// ----------------------------------------------------------------------
	public:
		static Constants& instance(){
			static Constants instance;
			return instance;
		}
		//! Copy C'tor
		Constants(Constants const&) = delete;
		//! Copy Operator
		void operator=(Constants const&) = delete;

	private:
		//! C'tor
		Constants();
		//! D'tor
		~Constants();

	// ----------------------------------------------------------------------
	//  Public Interface
	// ----------------------------------------------------------------------
	public:

		Q_PROPERTY(double radius READ radius WRITE setRadius NOTIFY radiusChanged)

		Q_PROPERTY(double granuleSeparation READ granuleSeparation WRITE setGranuleSeparation NOTIFY granuleSeparationChanged)
		Q_PROPERTY(double granuleRadius READ granuleRadius NOTIFY granuleRadiusChanged)
		Q_PROPERTY(double granuleMass READ granuleMass NOTIFY granuleMassChanged)
		Q_PROPERTY(double granuleForce READ granuleForce WRITE setGranuleForce NOTIFY granuleForceChanged)

		// The radius of the universe
		double radius() const;

		// The separation length between granules
		double granuleSeparation() const;

		// The radius of a single granule
		double granuleRadius() const;

		// The mass of single granule
		double granuleMass() const;

		// The separation force between the granules
		double granuleForce() const;

	public slots:
		void setRadius(double radius);
		void setGranuleSeparation(double granuleSeparation);
		void setGranuleForce(double granuleForce);

	signals:
		void radiusChanged(double radius);
		void granuleSeparationChanged(double granuleSeparation);
		void granuleRadiusChanged(double granuleRadius);
		void granuleMassChanged(double granuleMass);
		void granuleForceChanged(double granuleForce);

	// ----------------------------------------------------------------------
	//  Protected methods
	// ----------------------------------------------------------------------
	protected:

	// ----------------------------------------------------------------------
	//  Private members
	// ----------------------------------------------------------------------
	private:
		double                 _radius             = 1e-16;

		double                 _granuleSeparation  = 1e-20;
		double                 _granuleRadius;
		double                 _granuleMass;
		double                 _granuleForce       = cc;

		void calculateGranuleRadius();
		void calculateGranuleMass();
};
#define Constant Constants::instance()

} // Universe

#endif // CONSTANTS_H
