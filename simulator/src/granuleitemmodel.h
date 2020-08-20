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

#ifndef GRANULEITEMMODEL_H
#define GRANULEITEMMODEL_H

#include <QAbstractItemModel>
#include <QVector3D>

namespace SpaceTime {


class GranuleItemModel : public QAbstractItemModel
{
	Q_OBJECT
	// ----------------------------------------------------------------------
	//  X'truction
	// ----------------------------------------------------------------------
	public:
		GranuleItemModel();

	// ----------------------------------------------------------------------
	//  Public Interface
	// ----------------------------------------------------------------------
	public:

		// QAbstractItemModel interface
		QModelIndex index(int row, int column, const QModelIndex &parent) const;
		QModelIndex parent(const QModelIndex &child) const;
		int rowCount(const QModelIndex &parent) const;
		int columnCount(const QModelIndex &parent) const;
		QVariant data(const QModelIndex &index, int role) const;
		QHash<int, QByteArray> roleNames() const;

		enum Roles {
			RolePosition = Qt::UserRole,
			RoleOffset,
			RoleForce
		};

		typedef std::tuple<int, int, int> GranulePosition;
		typedef std::tuple<double, double, double> GranuleForce;

		Q_PROPERTY(int size READ size WRITE setSize NOTIFY sizeChanged)

		Q_INVOKABLE void update(double dt);

		int size() const;

	public slots:
		void setSize(int size);

	signals:
		void sizeChanged(int size);

	// ----------------------------------------------------------------------
	//  Protected methods
	// ----------------------------------------------------------------------


	protected:

	// ----------------------------------------------------------------------
	//  Private members
	// ----------------------------------------------------------------------
	private:

		int                            _size;

//		std::vector<GranulePosition>   _position;
		std::vector<QVector3D>   _position;
		std::vector<double>            _offset;
		std::vector<GranuleForce>      _force;

		void rebuildSpaceTime();
};

} // SpaceTime

#endif // GRANULEITEMMODEL_H
