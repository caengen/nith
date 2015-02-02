import entity.Salad;
import entity.User;

import javax.ejb.Stateless;
import javax.persistence.*;
import java.util.ArrayList;


@Stateless(name = "SessionEJB")
@PersistenceContext
public class UserHandlerBean {
    private EntityManagerFactory managerFactory;
    private EntityManager manager;
    private EntityTransaction transaction;

    private User user;


    public UserHandlerBean() {
        managerFactory = Persistence.createEntityManagerFactory("KimbanPUnit");
        manager = managerFactory.createEntityManager();
        transaction = manager.getTransaction();


    }

    //Create a new User object and persist it in the DB
    //Used when registering
    public User createUser(String id) {
        transaction.begin();
        user = new User(id, new ArrayList<Salad>());
        manager.persist(user);
        transaction.commit();

        return user;
    }

    //Add a Salad to User's List<Salad> and update the user
    public void updateUser(Salad salad) {
        transaction.begin();
        user.addSalad(salad);
        manager.persist(user);
        transaction.commit();
    }

    //Retrieve a user from the DB
    //Used when logging in
    public User findUser(String id) {
        transaction.begin();
        user = manager.find(User.class, id);
        transaction.commit();

        return user;
    }

    public User getUser() {
        return user;
    }

    public void setUser(User user) {
        this.user = user;
    }
}
